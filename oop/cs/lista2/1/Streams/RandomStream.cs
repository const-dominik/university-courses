namespace Streams;

class RandomStream : IntStream
{
    Random r;

    public RandomStream()
    {
        r = new Random();
    }

    override public bool eos()
    {
        return false;
    }

    override public int next()
    {
        return r.Next();
    }
}