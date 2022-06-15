using LazyList;
using System.Collections;

namespace PrimeCollection;

class PrimeCollection: IEnumerable, IEnumerator
{
    LazyPrimeList pl;
    int index;

    public PrimeCollection()
    {
        pl = new LazyPrimeList();
        index = 0;
    }

    private IEnumerator GetEnumerator()
    {
        return this;
    }

    IEnumerator IEnumerable.GetEnumerator()
    {
       return this;
    }

    public bool MoveNext()
    {
        this.index++;
        return !this.pl.checkEos();
    }

    public void Reset()
    {
        this.index = 0;
    }

    public int Current
    {
        get
        {
            return this.pl.element(index);
        }
    }

    object IEnumerator.Current
    {
        get 
        {
            return Current;
        }
    }
}

class Program
{
    static void Main(string[] args)
    {
        PrimeCollection pc = new PrimeCollection();
        foreach(int p in pc)
            Console.WriteLine(p);
    }
}