using LazyList;

namespace System;

class Program
{
    static void Main(string[] args)
    {
        LazyIntList list = new LazyIntList();
        Console.WriteLine($"dlugosc na poczatku: {list.size()}");
        Console.WriteLine($"element 40: {list.element(40)}");
        Console.WriteLine($"element 40 znow: {list.element(40)}");
        Console.WriteLine($"dlugosc: {list.size()}");
        Console.WriteLine($"element 38: {list.element(38)}");
        Console.WriteLine($"dlugosc: {list.size()}");
        
        LazyPrimeList primeList = new LazyPrimeList();
        Console.WriteLine("10 pierwszych liczb pierwszych");
        for (int i = 1; i <= 10; i++)
        {
            Console.WriteLine($"{primeList.element(i)}, size: {primeList.size()}");
        }
        Console.WriteLine($"piąta liczba pierwsza: {primeList.element(5)}, size: {primeList.size()}");
    }
}     