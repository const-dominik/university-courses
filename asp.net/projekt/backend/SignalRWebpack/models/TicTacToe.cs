namespace Coornick.Models
{
    public enum SidePick
    {
        CrossPlayer,
        CirclePlayer
    }

    public enum Result
    {
        CrossPlayer,
        CirclePlayer,
        Draw
    }
    public class TicTacToe
    {

        public string? CrossPlayer { get; set; }
        public string? CirclePlayer { get; set; }
        public SidePick? Turn { get; set; }
        public Pick?[] Board { get; set; } = new Pick?[9];
    }
}