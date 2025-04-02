namespace Coornick.Models
{
    public class RoomData
    {
        public string Name { get; set; } = string.Empty;
        public string Owner { get; set; } = string.Empty;
        public bool RequiresPassword { get; set; }
        public string? Password { get; set; }
    }

}