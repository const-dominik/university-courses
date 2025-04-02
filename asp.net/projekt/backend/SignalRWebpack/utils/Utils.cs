using Coornick.Models;

public static class Utils
{
    public static SidePick? CheckTTTWinner(Pick?[] board)
    {
        var lines = new List<int[]>
        {
            new[] {0, 1, 2},
            new[] {3, 4, 5},
            new[] {6, 7, 8},
            new[] {0, 3, 6},
            new[] {1, 4, 7},
            new[] {2, 5, 8},
            new[] {0, 4, 8},
            new[] {2, 4, 6}
        };

        foreach (var line in lines)
        {
            var a = line[0];
            var b = line[1];
            var c = line[2];
            if (board[a].HasValue && board[a] == board[b] && board[a] == board[c])
            {
                return board[a] == Pick.X ? SidePick.CrossPlayer : SidePick.CirclePlayer;
            }
        }

        return null;
    }

    public static bool CheckDraw(Pick?[] board)
    {
        return !board.Contains(null);
    }
}