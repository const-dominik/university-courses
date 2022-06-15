public class Program
{
    public static void main(String[] args)
    {
        LazyIntList list = new LazyIntList();
        LazyIntList list2 = new LazyIntList();
        list.add(10);
        list.print();
        list.remove(5);
        list.print();
        list.add(15);
        System.out.println(list.add(10)); //lista nie zmienila sie
        list.print();
        System.out.println(list.contains(5)); //false
        System.out.println(list.contains(10));
        System.out.println(list.contains(20));
        list2.add(4);
        System.out.println(list.containsAll(list2));
        list2.add(6);
        System.out.println(list.containsAll(list2));
        list.addAll(list2);
        System.out.println(list.contains(5));
        LazyIntList list3 = new LazyIntList();
        list3.add(10);
        list.removeAll(list3);
        list.print();
        list3.add(12);
        list.retainAll(list3); //11, 12
        list.print();
        list.clear();
        list.print();
    }
}
