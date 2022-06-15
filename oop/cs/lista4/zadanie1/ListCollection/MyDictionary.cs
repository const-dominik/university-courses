namespace ListCollection;

public class MyDictionary<K, V> : IListCollection<K, V>
{
    K[] keys;
    V[] values;
    int index;
    int length;

    public MyDictionary() {
        index = 0;
        length = 1;
        keys = new K[length];
        values = new V[length];
    }

    public bool includes(K key)
    {
        for (int i = 0; i < index; i++)
            if (keys[i]!.Equals(key)) return true;
        return false;
    }

    public void add(K key, V value)
    {
        if (includes(key)) return;
        if (index == length) {
            length++;
            Array.Resize(ref keys, length);
            Array.Resize(ref values, length);
        }
        keys[index] = key;
        values[index] = value;
        index++;
    }

    public void remove(K key)
    {
        for (int i = 0; i < index; i++)
        {
            if (keys[i]!.Equals(key)) {
                index--;
                for (int j = i; j < index; j++)
                {
                    keys[j] = keys[j+1];
                    values[j] = values[j+1];
                }
                break;
            }
        }
    }

    public V getItem(K key)
    {
        for (int i = 0; i < index; i++)
            if (keys[i]!.Equals(key)) return values[i];
        return default(V)!; //zwrócenie wartości podstawowej typu V gdy elementu nie ma w słowniku
    }

    public int size()
    {
        return this.length;
    }
}