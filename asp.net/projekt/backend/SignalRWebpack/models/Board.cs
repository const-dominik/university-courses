namespace Coornick.Models
{
    public enum Pick
    {
        X,
        O
    }

    public class Board
    {
        public Pick?[] Picks { get; set; }

        public Board()
        {
            Picks = new Pick?[9];
        }
    }
}
