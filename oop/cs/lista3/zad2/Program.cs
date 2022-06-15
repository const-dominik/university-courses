using System;
using MyDictionary;

class Program 
{
    static void Main(string[] args)
    {
        MyDictionary<string, int> dict = new MyDictionary<string, int>();
        dict.add("jeden", 1);
        dict.add("dwa", 2);
        dict.add("trzy", 3);
        Console.WriteLine(dict.find("a"));
        Console.WriteLine(dict.find("jeden"));
        Console.WriteLine(dict.find("dwa"));
        Console.WriteLine(dict.find("trzy"));
        dict.remove("dwa");
        Console.WriteLine(dict.find("dwa"));
    }
}