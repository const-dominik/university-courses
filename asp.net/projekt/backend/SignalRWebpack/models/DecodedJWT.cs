namespace Coornick.Models
{
    public class DecodedJWT
    {
        public string? Email { get; set; }
        public string? Nick { get; set; }
        public long Exp { get; set; }
    }

}