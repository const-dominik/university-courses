using System;

namespace Lista
{
    class Program
    {
        static void Main(string[] args) {
            MyList<int> lista = new MyList<int>();
            lista.print();
            Console.WriteLine(lista.is_empty());
            lista.push_back(1);
            lista.push_back(2);
            lista.push_back(3);
            lista.print();
            lista.push_front(0);
            lista.print();

            lista.pop_back();
            lista.print();
            lista.pop_front();
            lista.print();
        }
    }
}
