using MongoDB.Driver;

public class MongoDBClient
{
    private static MongoClient? _client;
    private static IMongoDatabase? _database;
    private static string? _mongoConnectionString;

    public static void Initialize(IConfiguration configuration)
    {
        _mongoConnectionString = configuration.GetConnectionString("MongoDB");
        _client = new MongoClient(_mongoConnectionString);
        _database = _client.GetDatabase("coornick");
    }

    public static IMongoDatabase GetDatabase()
    {
        if (_database == null)
        {
            throw new InvalidOperationException("MongoDB client has not been initialized. Call Initialize method first.");
        }

        return _database;
    }
}
