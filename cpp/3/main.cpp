#include <iostream>
#include "kolejka.hpp"

int main()
{
    kolejka queue(10);
    queue.wstaw("a");
    queue.wstaw("b");
    queue.wstaw("c");
    queue.wstaw("d");
    queue.printQueue();
    queue.usun();
    queue.usun();
    queue.printQueue();
    queue.wstaw("e");
    queue.printQueue();
    std::cout << queue.zprzodu() << std::endl << "------" << std::endl;

    kolejka q2({"a", "b", "c"});
    q2.printQueue();
    kolejka q3;
    std::cout << q3.dlugosc() << std::endl;

    q3 = q2;
    q2.printQueue();
    q3.printQueue();

    std::cout << "------\n";

    kolejka q4 = std::move(queue);
    q4.printQueue();
    queue.printQueue();

    return 0;
}