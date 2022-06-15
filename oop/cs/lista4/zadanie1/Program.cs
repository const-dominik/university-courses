using ListCollection;

class Program
{
    static void Main(string[] args)
    {
        bool testy1 = false;
        LazyIntList list = new LazyIntList();
        if (testy1)
        {
            //testy słownika i listy po implementacji IListCollection
            //testy MyDictionary
            MyDictionary<string, int> dict = new MyDictionary<string, int>();
            dict.add("jeden", 1);
            dict.add("dwa", 2);
            dict.add("trzy", 3);
            Console.WriteLine(dict.getItem("a"));
            Console.WriteLine(dict.getItem("jeden"));
            Console.WriteLine(dict.getItem("dwa"));
            Console.WriteLine(dict.getItem("trzy"));
            dict.remove("dwa");
            Console.WriteLine(dict.getItem("dwa"));
            Console.WriteLine("----------");

            //testy LazyList
            Console.WriteLine($"dlugosc na poczatku: {list.size()}");
            Console.WriteLine($"element 40: {list.getItem(40)}");
            Console.WriteLine($"element 40 znow: {list.getItem(40)}");
            Console.WriteLine($"dlugosc: {list.size()}");
            Console.WriteLine($"element 38: {list.getItem(38)}");
            Console.WriteLine($"dlugosc: {list.size()}");
        } else {
            list.getItem(10);
            //test IEnumerable
            foreach(int p in list)
                Console.Write($"{p} ");

            //test dostępu indeksowanego
            list[5] = 10;
            list[15] = 20;

            Console.WriteLine();
            foreach(int p in list)
                Console.Write($"{p} ");

            Console.WriteLine();
            Console.WriteLine(list); //toString, zwraca ostatni element z listy
            Console.WriteLine(list.Length); // właściwość Length
        }
    }
}