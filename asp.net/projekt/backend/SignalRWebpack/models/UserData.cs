using MongoDB.Bson;
using MongoDB.Bson.Serialization.Attributes;

namespace Coornick.Models
{
    public class UserData
    {
        [BsonId]
        [BsonRepresentation(BsonType.ObjectId)]
        public string Id { get; set; } = string.Empty;

        public string Email { get; set; } = string.Empty;
        public string Password { get; set; } = string.Empty;
        public string Nick { get; set; } = string.Empty;
        public int[] Stats { get; set; } = new int[3];
    }
}