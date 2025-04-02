using MongoDB.Bson;
using MongoDB.Bson.Serialization.Attributes;

namespace Coornick.Models
{
    public class GuestData
    {
        [BsonId]
        [BsonRepresentation(BsonType.ObjectId)]
        public string Id { get; set; } = string.Empty;

        public string Nick { get; set; } = string.Empty;
        public long Exp { get; set; }
    }

}