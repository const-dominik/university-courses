using System;

namespace MyDictionary
{
    public class MyDictionary<K, V>
    {
        K[] keys;
        V[] values;
        int index;
        int size;

        public MyDictionary() {
            index = 0;
            size = 1;
            keys = new K[size];
            values = new V[size];
        }

        public bool includes(K key)
        {
            for (int i = 0; i < index; i++)
                if (keys[i].Equals(key)) return true;
            return false;
        }

        public void add(K key, V value)
        {
            if (includes(key)) return;
            if (index == size) {
                size++;
                Array.Resize(ref keys, size);
                Array.Resize(ref values, size);
            }
            keys[index] = key;
            values[index] = value;
            index++;
        }

        public V find(K key)
        {
            for (int i = 0; i < index; i++)
                if (keys[i].Equals(key)) return values[i];
            return default(V); //zwrócenie wartości podstawowej typu V gdy elementu nie ma w słowniku
        }

        public void remove(K key)
        {
            for (int i = 0; i < index; i++)
            {
                if (keys[i].Equals(key)) {
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
    }
}