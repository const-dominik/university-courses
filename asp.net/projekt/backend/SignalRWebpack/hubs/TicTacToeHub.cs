using System;
using System.Collections.Concurrent;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.SignalR;
using Coornick.Models;
using MongoDB.Driver;
using System.Linq.Expressions;

public class TicTacToeHub : Hub
{
    private static readonly ConcurrentDictionary<string, Room> Rooms = new ConcurrentDictionary<string, Room>();
    private readonly TokenService _tokenService;
    private readonly IMongoDatabase _db = MongoDBClient.GetDatabase();

    public TicTacToeHub(TokenService tokenService)
    {
        _tokenService = tokenService;
    }

    private void TransferOwnership(HashSet<string> socketRoom, Room gameRoom, DecodedJWT data, string room)
    {
        if (gameRoom.Data.Owner == data.Nick)
        {
            var users = socketRoom.Where(id => id != Context.ConnectionId).ToList();
            var random = new Random();
            var randomUser = users[random.Next(users.Count)];
            DecodedJWT? decodedData = _tokenService.DecodeToken(randomUser);
            if (decodedData == null)
            {
                return;
            }
            if (decodedData.Nick == null) return;
            gameRoom.Data.Owner = decodedData.Nick;

            Clients.Group(room).SendAsync("roomData", gameRoom);
            Clients.Group(room).SendAsync("message", "[SYSTEM]", $"Owner left room, ownership transferred to {decodedData.Nick}", room);
        }
    }

    private async Task<bool> AddScoreAsync(string nick, string score)
    {
        var usersCollection = _db.GetCollection<UserData>("users");

        var user = await usersCollection.Find(u => u.Nick == nick).FirstOrDefaultAsync();
        if (user != null)
        {
            if (score == "win")
            {
                user.Stats[0]++;
            }
            else if (score == "lose")
            {
                user.Stats[2]++;
            }
            else
            {
                user.Stats[1]++;
            }

            var update = Builders<UserData>.Update.Set(u => u.Stats, user.Stats);
            var result = await usersCollection.UpdateOneAsync(u => u.Nick == nick, update);

            if (result.IsAcknowledged)
            {
                return true;
            }
        }

        return false;
    }

    private async Task HandleDisconnection(Room room, string nick, bool scoreCounts, string roomId)
    {
        SidePick? playedAs = null;
        if (room.Players.Count == 0)
        {
            Rooms.TryRemove(roomId, out var value);
            await Clients.All.SendAsync("removeRoom", roomId);
        }
        if (room.Game.CirclePlayer == nick)
        {
            playedAs = SidePick.CirclePlayer;
            room.Game.CirclePlayer = null;
        }
        else if (room.Game.CrossPlayer == nick)
        {
            playedAs = SidePick.CrossPlayer;
            room.Game.CrossPlayer = null;
        }

        if (playedAs.HasValue)
        {
            await Clients.Group(roomId).SendAsync("sidePicked", playedAs.Value.ToString(), null);

            if (room.Game.Turn.HasValue)
            {
                room.Game.Turn = null;
                var oppositeSide = GetOppositeSide(playedAs.Value);

                if (oppositeSide == SidePick.CirclePlayer)
                {
                    room.Game.CrossPlayer = null;
                    if (scoreCounts && room.Game.CirclePlayer != null)
                    {
                        await Clients.Group(roomId).SendAsync("winner", new Winner((Result)oppositeSide, room.Game.CirclePlayer), true);


                        await AddScoreAsync(nick, "lose");
                        await AddScoreAsync(room.Game.CirclePlayer, "win");
                    }
                }
                else if (oppositeSide == SidePick.CrossPlayer)
                {
                    room.Game.CirclePlayer = null;
                    if (scoreCounts && room.Game.CrossPlayer != null)
                    {
                        await Clients.Group(roomId).SendAsync("winner", new Winner((Result)oppositeSide, room.Game.CrossPlayer), true);
                        await AddScoreAsync(nick, "lose");
                        await AddScoreAsync(room.Game.CrossPlayer, "win");
                    }
                }
                var message = $"The game has been stopped, because {nick} surrendered.";
                await Clients.Group(roomId).SendAsync("message", "[SYSTEM]", message, roomId);
            }
        }
    }

    public override async Task OnConnectedAsync()
    {
        var httpContext = Context.GetHttpContext();
        if (httpContext != null && httpContext.Request.Cookies.TryGetValue("token", out var token))
        {
            _tokenService.UpdateTokenOwner(token, Context.ConnectionId);
        }
        await base.OnConnectedAsync();
    }


    private SidePick GetOppositeSide(SidePick side)
    {
        return side == SidePick.CirclePlayer ? SidePick.CrossPlayer : SidePick.CirclePlayer;
    }

    private bool CheckIfSocketIsInRoom(string roomId)
    {
        var room = Rooms.GetValueOrDefault(roomId);
        var token = _tokenService.GetTokenFromMap(Context.ConnectionId);
        if (token == null) return false;
        return room != null && room.Players.Contains(token);
    }

    public async Task Join()
    {
        var rooms = Rooms.Select(room => new { room.Key, room.Value.Data }).ToList();
        await Clients.Caller.SendAsync("newRoom", rooms);
    }

    public async Task JoinRoom(string roomId)
    {
        var room = Rooms.GetValueOrDefault(roomId);
        if (room != null)
        {
            await Clients.Caller.SendAsync("roomData", room);
        }
    }

    public async Task LeaveRoom(string roomId)
    {
        var room = Rooms.GetValueOrDefault(roomId);
        if (room != null)
        {
            await Groups.RemoveFromGroupAsync(Context.ConnectionId, roomId);
            var token = _tokenService.GetTokenFromMap(Context.ConnectionId);
            if (token == null) return;
            room.Players.Remove(token);
        }
    }

    public async Task AddRoom(RoomData roomData)
    {
        var roomId = Guid.NewGuid().ToString();
        if (Rooms.Values.Any(room => room.Data.Name == roomData.Name)) return;

        var room = new Room
        {
            Data = roomData,
            Id = roomId,
            Game = new TicTacToe
            {
                CrossPlayer = null,
                CirclePlayer = null,
                Turn = null,
                Board = new Pick?[9]
            }
        };

        Rooms.TryAdd(roomId, room);
        var roomList = new List<object> { new { Key = roomId, Data = roomData } };
        await Clients.All.SendAsync("newRoom", roomList);
        await Clients.Caller.SendAsync("roomAdded", roomId);
    }

    public async Task DoesRoomExist(string roomId)
    {
        var room = Rooms.GetValueOrDefault(roomId);
        if (room == null)
        {
            await Clients.Caller.SendAsync("roomError");
        }
    }

    public async Task GetRoom(string roomId, string password, string jwt)
    {
        var room = Rooms.GetValueOrDefault(roomId);
        if (room == null)
        {
            await Clients.Caller.SendAsync("roomError");
            return;
        }

        var roomData = room.Data;

        DecodedJWT? decodedData = _tokenService.DecodeToken(jwt);
        if (decodedData == null)
        {
            return;
        }

        if (!roomData.RequiresPassword || password == roomData.Password || roomData.Owner == decodedData.Nick)
        {
            await Groups.AddToGroupAsync(Context.ConnectionId, roomId);
            var token = _tokenService.GetTokenFromMap(Context.ConnectionId);
            if (token == null) return;
            room.Players.Add(token);
            await Clients.Caller.SendAsync("roomData", room);
        }
        else
        {
            await Clients.Caller.SendAsync("roomRequiresPassword", password != null);
        }
    }

    public async Task Message(string roomId, string message, string jwt)
    {
        DecodedJWT? decodedData = _tokenService.DecodeToken(jwt);
        if (decodedData == null)
        {
            return;
        }
        if (message.Length > 100) return;

        var room = Rooms[roomId];
        if (room == null) return;

        await Clients.Group(roomId).SendAsync("message", decodedData.Nick, message, roomId);
    }

    public async Task PickSide(string id, string side, string jwt)
    {
        if (!Enum.TryParse<SidePick>(side, true, out var sidePick))
        {
            throw new ArgumentException("Invalid side value");
        }
        DecodedJWT? decodedData = _tokenService.DecodeToken(jwt);
        if (decodedData == null)
        {
            return;
        }
        var nick = decodedData.Nick;

        if (CheckIfSocketIsInRoom(id) && nick != null)
        {
            if (Rooms.TryGetValue(id, out var room))
            {
                if (side == null)
                {
                    await HandleDisconnection(room, nick, true, id);
                    return;
                }
                if (sidePick == SidePick.CirclePlayer && room.Game.CirclePlayer == null ||
                    sidePick == SidePick.CrossPlayer && room.Game.CrossPlayer == null)
                {
                    if (sidePick == SidePick.CirclePlayer)
                    {
                        room.Game.CirclePlayer = nick;
                        if (room.Game.CrossPlayer == nick)
                        {
                            room.Game.CrossPlayer = null;
                        }
                    }
                    else
                    {
                        room.Game.CrossPlayer = nick;
                        if (room.Game.CirclePlayer == nick)
                        {
                            room.Game.CirclePlayer = null;
                        }
                    }

                    await Clients.Group(id).SendAsync("sidePicked", side.ToString(), nick);

                    if (room.Game.CirclePlayer != null && room.Game.CrossPlayer != null && room.Game.Turn == null)
                    {
                        var random = new Random();
                        var randomStart = (SidePick)random.Next(0, 2);
                        room.Game.Turn = randomStart;
                        room.Game.Board = new Pick?[9];
                        await Clients.Group(id).SendAsync("startGame", randomStart.ToString());
                    }
                }
            }
        }
    }

    public async Task Kick(string side, string id, string jwt)
    {
        if (!Enum.TryParse<SidePick>(side, true, out var sidePick))
        {
            throw new ArgumentException("Invalid side value");
        }
        DecodedJWT? decodedData = _tokenService.DecodeToken(jwt);
        if (decodedData == null)
        {
            return;
        }
        if (Rooms.TryGetValue(id, out var room))
        {
            string? player = sidePick == SidePick.CrossPlayer ? room.Game.CrossPlayer : room.Game.CirclePlayer;
            if (player != null)
            {
                if (room.Data.Owner == decodedData.Nick || player == decodedData.Nick)
                {
                    if (room.Game.Turn == null)
                    {
                        if (sidePick == SidePick.CrossPlayer)
                            room.Game.CrossPlayer = null;
                        else
                            room.Game.CirclePlayer = null;

                        await Clients.Group(id).SendAsync("sidePicked", side, null);
                    }
                    else
                    {
                        string message;
                        if (room.Data.Owner == decodedData.Nick && player != decodedData.Nick)
                        {
                            message = "The game has been stopped, because room owner kicked one of the players.";
                            await Clients.Group(id).SendAsync("stopGame", "Owner kicked a guy.");
                        }
                        else
                        {
                            message = $"The game has been stopped, because {decodedData.Nick} surrendered.";
                            var oppositeSide = GetOppositeSide(sidePick);
                            string? oppositeNick = oppositeSide == SidePick.CrossPlayer ? room.Game.CrossPlayer : room.Game.CirclePlayer;
                            string? sideNick = sidePick == SidePick.CrossPlayer ? room.Game.CrossPlayer : room.Game.CirclePlayer;
                            if (oppositeNick == null || sideNick == null) return;
                            await AddScoreAsync(oppositeNick, "win");
                            await AddScoreAsync(sideNick, "lose");
                            await Clients.Group(id).SendAsync("winner", new Winner((Result)oppositeSide, oppositeNick), true);
                            await Clients.Group(id).SendAsync("stopGame", "Player surrendered.");
                        }

                        if (sidePick == SidePick.CrossPlayer)
                            room.Game.CrossPlayer = null;
                        else
                            room.Game.CirclePlayer = null;

                        room.Game.Turn = null;
                        await Clients.Group(id).SendAsync("message", "[SYSTEM]", message, id);
                        await Clients.Group(id).SendAsync("sidePicked", side, null);
                    }
                }
            }
        }
    }

    public async Task Move(string id, int index, string jwt)
    {
        DecodedJWT? decodedData = _tokenService.DecodeToken(jwt);
        if (decodedData == null)
        {
            return;
        }
        var player = decodedData.Nick;
        if (Rooms.TryGetValue(id, out var room))
        {
            var game = room.Game;

            if (game.Board[index] != null || game.Turn == null) return;

            var currentTurn = game.Turn == SidePick.CrossPlayer ? game.CrossPlayer : game.CirclePlayer;
            if (currentTurn != player) return;

            Pick? pick = null;
            if (game.CirclePlayer == player)
                pick = Pick.O;
            else if (game.CrossPlayer == player)
                pick = Pick.X;

            if (pick != null)
            {
                game.Board[index] = pick;
                await Clients.Group(id).SendAsync("move", index, pick);
                var winner = Utils.CheckTTTWinner(game.Board);
                var draw = Utils.CheckDraw(game.Board);
                if (winner != null)
                {
                    var loserNick = winner == SidePick.CrossPlayer ? game.CirclePlayer : game.CrossPlayer;
                    var winnerNick = winner == SidePick.CrossPlayer ? game.CrossPlayer : game.CirclePlayer;
                    if (loserNick == null || winnerNick == null) throw new Exception("shouldn't happen");
                    game.Turn = null;
                    await AddScoreAsync(winnerNick, "win");
                    await AddScoreAsync(loserNick, "lose");
                    await Clients.Group(id).SendAsync("winner", new Winner((Result)(SidePick)winner, winnerNick), false);
                }
                else if (draw)
                {
                    var circle = game.CirclePlayer;
                    var cross = game.CrossPlayer;
                    if (circle == null || cross == null) throw new Exception("shouldn't happen");
                    game.Turn = null;
                    await AddScoreAsync(circle, "draw");
                    await AddScoreAsync(cross, "draw");
                    await Clients.Group(id).SendAsync("winner", new Winner(Result.Draw, ""), false);
                }
                else
                {
                    game.Turn = GetOppositeSide(game.Turn.Value);
                }
            }
        }
    }

    public async Task Restart(string id)
    {
        if (Rooms.TryGetValue(id, out var room))
        {
            if (CheckIfSocketIsInRoom(id))
            {
                if (room.Game.CirclePlayer != null && room.Game.CrossPlayer != null && room.Game.Turn == null)
                {
                    var random = new Random();
                    var randomStart = (SidePick)random.Next(0, 2);
                    room.Game.Turn = randomStart;
                    room.Game.Board = new Pick?[9];
                    await Clients.Group(id).SendAsync("startGame", randomStart.ToString());
                }
            }
        }
    }

    public async Task HandleLeave()
    {
        var jwt = _tokenService.GetTokenFromMap(Context.ConnectionId);
        if (jwt == null) return;

        DecodedJWT? decodedData = _tokenService.DecodeToken(jwt);
        if (decodedData == null)
        {
            return;
        }
        var nick = decodedData.Nick;
        foreach (var room in Rooms)
        {
            if (!room.Value.Players.Contains(jwt)) continue;

            room.Value.Players.Remove(jwt);
            if (room.Value.Players.Count == 0)
            {
                Rooms.TryRemove(room.Key, out var value);
                await Clients.All.SendAsync("removeRoom", room.Key);
            }
            else
            {
                if (nick != null)
                    await HandleDisconnection(room.Value, nick, true, room.Key);

                TransferOwnership(room.Value.Players, room.Value, decodedData, room.Key);
            }

        }
    }

    public override async Task OnDisconnectedAsync(Exception? exception)
    {
        var jwt = _tokenService.GetTokenFromMap(Context.ConnectionId);
        if (jwt == null) return;
        DecodedJWT? decodedData = _tokenService.DecodeToken(jwt);
        if (decodedData == null)
        {
            return;
        }
        foreach (var room in Rooms)
        {
            if (!room.Value.Players.Contains(jwt)) continue;

            room.Value.Players.Remove(jwt);
            await Groups.RemoveFromGroupAsync(Context.ConnectionId, room.Key);

            if (room.Value.Players.Count == 0)
            {
                Rooms.TryRemove(room.Key, out var value);
                await Clients.All.SendAsync("removeRoom", room.Key);
                continue;
            }

            if (decodedData.Nick != null)
                await HandleDisconnection(room.Value, decodedData.Nick, true, room.Key);
            TransferOwnership(room.Value.Players, room.Value, decodedData, room.Key);
        }

        _tokenService.jwts.Remove(Context.ConnectionId);

        await base.OnDisconnectedAsync(exception);
    }

    public async Task DeleteRoom(string room)
    {
        if (Rooms.ContainsKey(room))
        {
            Rooms.TryRemove(room, out var val);
            await Clients.All.SendAsync("removeRoom", room);
        }
    }

    //          _    _ _______ _    _ 
    //     /\  | |  | |__   __| |  | |
    //    /  \ | |  | |  | |  | |__| |
    //   / /\ \| |  | |  | |  |  __  |
    //  / ____ \ |__| |  | |  | |  | |
    // /_/    \_\____/   |_|  |_|  |_|

    public async Task Register(RegisterData data)
    {
        try
        {
            if (data.Nick.Contains("@") || !data.Email.Contains("@"))
            {
                throw new System.Exception("Invalid nick or email");
            }
            IMongoCollection<UserData> usersCollection = _db.GetCollection<UserData>("users");
            IMongoCollection<GuestData> guestCollection = _db.GetCollection<GuestData>("guests");

            var checkEmailTask = usersCollection.Find(x => x.Email == data.Email).FirstOrDefaultAsync();
            var checkNickTask = usersCollection.Find(x => x.Nick == data.Nick).FirstOrDefaultAsync();
            var checkGuestsTask = guestCollection.Find(x => x.Nick == data.Nick).FirstOrDefaultAsync();

            await Task.WhenAll(checkEmailTask, checkNickTask, checkGuestsTask);

            var checkEmail = checkEmailTask.Result;
            var checkNick = checkNickTask.Result;
            var checkGuests = checkGuestsTask.Result;

            if (checkEmail == null && checkNick == null && (checkGuests == null || checkGuests.Exp < DateTimeOffset.UtcNow.ToUnixTimeSeconds()))
            {
                if (checkGuests != null)
                {
                    await guestCollection.DeleteOneAsync(x => x.Nick == data.Nick);
                }
                var salt = BCrypt.Net.BCrypt.GenerateSalt(10);
                var entry = new UserData
                {
                    Nick = data.Nick,
                    Email = data.Email,
                    Password = BCrypt.Net.BCrypt.HashPassword(data.Password, salt),
                    Stats = new int[3]
                };

                try
                {
                    await usersCollection.InsertOneAsync(entry);
                    string token = _tokenService.CreateToken(Context.ConnectionId, data.Nick, data.Email);
                    await Clients.Caller.SendAsync("authOK", token);
                }
                catch (MongoDB.Driver.MongoWriteException)
                {
                    await Clients.Caller.SendAsync("authFail", "internal server error");
                }
            }
            else if (checkGuests != null)
            {
                double expIn = (checkGuests.Exp - DateTimeOffset.UtcNow.ToUnixTimeSeconds()) / (60 * 60);
                await Clients.Caller.SendAsync("authFail", $"This nick is currently taken by a guest, it'll be valid for the next {expIn:F2}h.");
            }
            else
            {
                string message = checkEmail != null ? "Email already in database" : "This nick is taken";
                await Clients.Caller.SendAsync("authFail", message);
            }
        }
        catch (System.Exception)
        {

            throw;
        }
    }

    public async Task Login(LoginData data)
    {
        try
        {
            IMongoCollection<UserData> usersCollection = _db.GetCollection<UserData>("users");

            Expression<Func<UserData, bool>> filter;
            if (data.Identifier.Contains("@"))
            {
                filter = user => user.Email == data.Identifier;
            }
            else
            {
                filter = user => user.Nick == data.Identifier;
            }

            var user = await usersCollection.Find(filter).FirstOrDefaultAsync();
            if (user != null)
            {
                bool isPasswordValid = BCrypt.Net.BCrypt.Verify(data.Password, user.Password);
                if (isPasswordValid)
                {
                    string token = _tokenService.CreateToken(Context.ConnectionId, user.Nick, user.Email);
                    await Clients.Caller.SendAsync("authOK", token);
                    return;
                }
            }
            await Clients.Caller.SendAsync("authFail", "User not found");
        }
        catch (Exception e)
        {
            Console.WriteLine("login", e);
        }
    }

    public async Task Guest(string nick)
    {
        try
        {
            IMongoCollection<UserData> usersCollection = _db.GetCollection<UserData>("users");
            IMongoCollection<GuestData> guestsCollection = _db.GetCollection<GuestData>("guests");

            var checkNickTask = usersCollection.Find(user => user.Nick == nick).FirstOrDefaultAsync();
            var checkGuestNickTask = guestsCollection.Find(guest => guest.Nick == nick).FirstOrDefaultAsync();

            await Task.WhenAll(checkNickTask, checkGuestNickTask);

            var user = checkNickTask.Result;
            var guest = checkGuestNickTask.Result;

            if (user == null)
            {
                if (guest == null || guest.Exp < DateTimeOffset.UtcNow.ToUnixTimeSeconds())
                {
                    if (guest != null)
                    {
                        await guestsCollection.DeleteOneAsync(x => x.Nick == nick);
                    }
                    var entry = new GuestData
                    {
                        Nick = nick,
                        Exp = DateTimeOffset.UtcNow.AddDays(1).ToUnixTimeSeconds()
                    };
                    await guestsCollection.InsertOneAsync(entry);
                    string token = _tokenService.CreateToken(Context.ConnectionId, nick, null, DateTime.Now.AddDays(1));
                    await Clients.Caller.SendAsync("authOK", token);
                }
                else
                {
                    double expIn = (guest.Exp - DateTimeOffset.UtcNow.ToUnixTimeSeconds()) / (60 * 60);
                    await Clients.Caller.SendAsync("authFail", $"This nick is currently taken by guest, it'll be valid for the next {expIn:F2}h.");
                }
            }
            else
            {
                await Clients.Caller.SendAsync("authFail", "Nick is taken");
            }
        }
        catch (Exception e)
        {
            Console.WriteLine(e);
            await Clients.Caller.SendAsync("authFail", "Nick is taken");
        }
    }

    public async Task CheckTokenValidity(string jwt)
    {
        DecodedJWT? decodedData = _tokenService.DecodeToken(jwt);
        if (decodedData == null)
        {
            await Clients.Caller.SendAsync("isTokenOk", false);
            return;
        }

        if (decodedData.Exp != 0 && DateTimeOffset.UtcNow.ToUnixTimeSeconds() < decodedData.Exp)
        {
            await Clients.Caller.SendAsync("isTokenOk", true);
        }
        else
        {
            await Clients.Caller.SendAsync("isTokenOk", false);
        }
    }
    /*

      _____  _____   ____  ______ _____ _      ______ 
     |  __ \|  __ \ / __ \|  ____|_   _| |    |  ____|
     | |__) | |__) | |  | | |__    | | | |    | |__   
     |  ___/|  _  /| |  | |  __|   | | | |    |  __|  
     | |    | | \ \| |__| | |     _| |_| |____| |____ 
     |_|    |_|  \_\\____/|_|    |_____|______|______|


    */

    public async Task GetProfile(string jwt)
    {
        DecodedJWT? decodedData = _tokenService.DecodeToken(jwt);
        if (decodedData == null)
        {
            return;
        }
        if (string.IsNullOrEmpty(decodedData.Email)) return;

        var usersCollection = _db.GetCollection<UserData>("users");

        var user = await usersCollection.Find(u => u.Email == decodedData.Email).FirstOrDefaultAsync();
        if (user == null)
        {
            Console.WriteLine("shouldn't happen, user not found even though jwt has email");
            return;
        }

        var profileData = new ProfileData
        {
            Nick = user.Nick,
            Stats = user.Stats
        };

        await Clients.Caller.SendAsync("profile", profileData);
    }

    public async Task GetRanking()
    {
        try
        {
            var usersCollection = _db.GetCollection<UserData>("users");

            var users = await usersCollection.Find(_ => true)
                .SortByDescending(u => u.Stats[0])
                .Limit(20)
                .ToListAsync();

            var ranking = users.Select(user => new { user.Nick, Wins = user.Stats[0] });

            await Clients.Caller.SendAsync("getRanking", ranking);
        }
        catch (Exception e)
        {
            Console.WriteLine("ranking", e);
        }
    }

}