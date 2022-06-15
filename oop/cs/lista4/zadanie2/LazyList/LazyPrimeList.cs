using Streams;

namespace LazyList;
    
class LazyPrimeList : LazyIntList
{
    PrimeStream ps;
    public LazyPrimeList()
    {
        ps = new PrimeStream();
    }

    override protected void buildListToIndex(int index)
    {
        for (int i = this.length + 1; i <= index; i++)
        {
            this.list.Add(ps.next());
        }
    }

    public bool checkEos()
    {
        return ps.eos();
    }
}