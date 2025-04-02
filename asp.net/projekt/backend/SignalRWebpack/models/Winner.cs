namespace Coornick.Models
{

    public class Winner
    {
        public Result Result { get; set; }
        public string Player { get; set; }

        public Winner(Result result, string player)
        {
            Result = result;
            Player = player;
        }
    }
}