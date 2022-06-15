import java.util.List;
import java.util.ArrayList;

class LazyIntList implements java.io.Serializable
{
    protected int length;
    protected List<Integer> list;

    public LazyIntList()
    {   
        length = 0;
        list = new ArrayList<Integer>(List.of(0));
    }

    protected void buildListToIndex(int index)
    {
        for (int i = this.length + 1; i <= index; i++)
        {
            this.list.add(i);
        }
    }

    public int element(int i)
    {
        if (this.length < i)
        {
            this.buildListToIndex(i);
            this.length = i;
        }
        return this.list.get(i);
    }

    public int size()
    {
        return this.length;
    }
}