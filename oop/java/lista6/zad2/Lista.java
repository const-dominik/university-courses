import java.util.List;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;

class LazyIntList implements Collection<Integer>
{
    class MyIterator<T> implements Iterator<Integer> {
        int index;

        public MyIterator() {
            index = 0;
        }

        public boolean hasNext()
        {
            for (int i = index + 1; i <= length; i++)
                if (list.get(i) != -1) return true;
            return false;
        }

        public Integer next()
        {
            for (int i = index + 1; i <= length; i++)
                if (list.get(i) != -1)
                {
                    index = i;
                    break;
                }
            return list.get(index);
        }
    }

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

    public <T> T[] toArray(T[] a)
    {
        return list.toArray(a);
    }

    public Object[] toArray()
    {
        return list.toArray();
    }

    public Iterator<Integer> iterator()
    {
        return new MyIterator<Integer>();
    }

    public boolean containsAll(Collection<?> collection)
    {
        return this.list.containsAll(collection);
    }

    public boolean addAll(Collection<? extends Integer> collection)
    {
        boolean changed = false;
        for (Integer a : collection)
            if (add(a)) changed = true;
        return changed;
    }

    public boolean removeAll(Collection<?> collection)
    {
        boolean changed = false;
        for (int i = 1; i <= length; i++)
            if (collection.contains(this.list.get(i))) {
                this.list.set(i, -1);
                changed = true;
            }
        return changed;
    }

    public boolean retainAll(Collection<?> collection)
    {
        boolean changed = false;
        for (int i = 1; i <= length; i++)
            if (!collection.contains(this.list.get(i))) {
                this.list.set(i, -1);
                changed = true;
            }
        return changed;
    }

    public int size()
    {
        return this.length;
    }

    public boolean isEmpty()
    {
        return this.length == 0;
    }

    public boolean contains(Object a)
    {
        for (int i = 1; i <= length; i++)
            if (this.list.get(i) == a) {
                return true;
            }
        return false;
    }

    public boolean add(Integer a)
    {
        if (this.contains(a)) 
            return false;
        if (a > this.length) {
            buildListToIndex(a);
            this.length = a;
        } else {
            this.list.set(a, a);
        }
        return true;
    }

    public boolean remove(Object a)
    {
        boolean changed = false;
        for (int i = 1; i <= length; i++)
            if (this.list.get(i) == a) {
                this.list.set(i, -1);
                changed = true;
                break;
            }
        return changed;
    }

    public void clear()
    {
        this.length = 0;
        list.clear();
    }

    public void print()
    {
        Iterator<Integer> it = iterator();
        while (it.hasNext()) {
            System.out.print(it.next());
            System.out.print(" ");
        }
        System.out.println();
    }
}