namespace Coornick.Models
{
    public class Room
    {
        public RoomData Data { get; set; } = new RoomData();
        public string Id { get; set; } = string.Empty;
        public TicTacToe Game { get; set; } = new TicTacToe();
        public HashSet<string> Players { get; set; } = new HashSet<string>();

    }

}