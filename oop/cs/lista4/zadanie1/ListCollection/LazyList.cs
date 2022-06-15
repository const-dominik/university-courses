using System.Collections;

namespace ListCollection;

class LazyIntList : IListCollection<int, int>, IEnumerable
{
    protected int length;
    protected List<int> list;

    public LazyIntList()
    {   
        length = 0;
        list = new List<int>{0};
    }

    virtual public void add(int start, int last)
    {
        for (int i = start; i <= last; i++)
        {
            this.list.Add(i);
        }
    }

    public int getItem(int i)
    {
        if (this.length < i)
        {
            this.add(this.length + 1, i);
            this.length = i;
        }
        return this.list[i];
    }

    public int size()
    {
        return this.length;
    }

    public int this[int indeks]
    {
        get
        {
            if (indeks <= 0)
                throw new Exception("index must be greater than 0");
            return this.getItem(indeks);
        }

        set
        {
            if (indeks <= 0)
                throw new Exception("index must be greater than 0");
            if (indeks > this.length)
                this.getItem(indeks);

            this.list[indeks] = value;
        }
    }

    public int Length
    {
        get
        {
            return this.size();
        }
    }

    public override string ToString()
    {
        if (this.size() != 0) return this.list[this.length].ToString();
        return "";
    }

    public IEnumerator GetEnumerator()
    {
        return new LazyListEnumerator(this.list, this.length);
    }

    IEnumerator IEnumerable.GetEnumerator()
    {
        return new LazyListEnumerator(this.list, this.length);
    }
}

public class LazyListEnumerator : IEnumerator
{
    protected int index;
    protected int length;
    protected List<int> list;

    public LazyListEnumerator(List<int> list, int length)
    {
        this.list = list;
        this.length = length;
        this.index = 0;
    }

    public bool MoveNext()
    {
        this.index++;
        return this.index <= this.length;
    }

    public void Reset()
    {
        this.length = 0;
    }

    public int Current
    {
        get
        {
            return list[index];
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