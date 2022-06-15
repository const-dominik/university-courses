namespace LazyList;

class LazyIntList
{
    protected int length;
    protected List<int> list;

    public LazyIntList()
    {   
        length = 0;
        list = new List<int>{0};
        //z 0 na indeksie 0 zeby lista dzialala na indeksach [1, length], bo chyba taka jest wymagana w zadaniu
    }

    virtual protected void buildListToIndex(int index)
    {
        for (int i = this.length + 1; i <= index; i++)
        {
            this.list.Add(i);
        }
    }

    public int element(int i)
    {
        if (this.length < i)
        {
            this.buildListToIndex(i);
            this.length = i;
        }
        return this.list[i];
    }

    public int size()
    {
        return this.length;
    }
}