namespace ListCollection;

interface IListCollection<K, V>
{
    void add(K a, V b);
    int size();
    V getItem(K key);
}