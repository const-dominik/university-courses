namespace Streams;

class RandomWordStream {
    PrimeStream ps;
    RandomStream rs;

    public RandomWordStream()
    {
        ps = new PrimeStream();
        rs = new RandomStream();
    }

    public string next()
    {
        string result = "";
        int prime = ps.next();
        for (int i = 0; i < prime; i++)
        {
            int randomAscii = (rs.next() % 94) + 32;
            result += ((char)randomAscii).ToString();
        }
        return result;
    }
}