using Streams;

namespace System;

class Program
{
    static void Main(string[] args)
    {
        IntStream ints = new IntStream();
        PrimeStream ps = new PrimeStream();
        RandomStream rs = new RandomStream();
        RandomWordStream rws = new RandomWordStream();
        
        Console.WriteLine("integers");
        for (int i = 0; i < 5; i++) Console.WriteLine(ints.next());
        Console.WriteLine("primes");
        for (int i = 0; i < 5; i++) Console.WriteLine(ps.next());
        Console.WriteLine("random nums");
        for (int i = 0; i < 5; i++) Console.WriteLine(rs.next());
        Console.WriteLine("random strings");
        for (int i = 0; i < 5; i++) Console.WriteLine(rws.next());
    }
}