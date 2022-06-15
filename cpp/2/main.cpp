//329595, Dominik Kiełbowicz, zadanie 2
#include <iostream>
#include <string>
#include "zmienna.hpp"
#include "zbior_zmiennych.hpp"

using namespace std;

int main()
{
    zmienna a, b("zmienna"), c("zmienna2", 3.2);
    //zmienna d("1asdasd"), e("sdflk`km"), f(""); //proba utworzenia zmiennej ze zla nazwa

    std::cout << a.get_name() << " " << a.get_value() << std::endl;
    std::cout << b.get_name() << " " << b.get_value() << std::endl;
    std::cout << c.get_name() << " " << c.get_value() << std::endl;
    c.change_value(4.2);
    std::cout << c.get_name() << " " << c.get_value() << std::endl;

    std::cout << "Zbiory" << std::endl;
    zbior_zmiennych zbior(3);
    zbior.add(a);
    zbior.add(b);
    zbior.add(c);
    zbior.print();
    zbior.remove(a);
    zbior.print();
    zbior.add(a);
    zbior.print();
    zbior.modify(a, 5.0);
    zbior.print();
    std::cout << zbior.includes(a) << std::endl;
    zbior.remove(a);
    std::cout << zbior.includes(a) << std::endl;
    std::cout << zbior.getValue(c);
}