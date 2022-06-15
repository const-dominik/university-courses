//Dominik Kiełbowicz, 329595, lista 5
#include <iostream>
#include "kolornazwany.hpp"
#include "kolortransparentny.hpp"
#include "kolory.hpp"
#include "punkt.hpp"
#include "punkt2d.hpp"
#include "punkt3d.hpp"
#include "punktkolorowy.hpp"
#include "punktkolorowynazwany.hpp"
#include "punktnazwany.hpp"
#include "wektor2d.hpp"
#include "wektor3d.hpp"


int main()
{
    kolory a;
    a.setG(30);
    kolory b(200,150,100);
    kolortransparentny g(3, 4, 5, 233);
    kolornazwany c;
    kolornazwany d(1, 2, 3, 4, "nazwa");
    punkt e;
    punkt f(1.0, 2.0);
    punkt f2(5.0, 1.0);
    punkt2d h(3.0, 4.0);
    wektor2d h2(1.0, 2.5);
    punkt3d i(2.2, 3.0, 4.0);
    punkt3d i2(1.0, 5.0, 1.0);
    punkt3d i3(3.1, 3.5, 2.0);
    punktkolorowy j(3.0, 1.0, g);
    punktnazwany k(5.0, 1.0, "punkcik");
    punktkolorowynazwany l(3.4, 5.6, g, "pktkolorowy");
    a.wypisz();
    b.wypisz();
    std::cout << kolory::sumColor(b) << std::endl;
    g.wypisz();
    g.setAlfa(42);
    g.wypisz();
    c.wypisz();
    c.setName("nowaNazwa");
    c.wypisz();
    d.wypisz();
    e.wypisz();
    f.wypisz();
    f2.wypisz();
    std::cout << "wspoliniowe: " << punkt::wspolliniowe(e, f, f2) << " dystans: " << e.odleglosc(f) << std::endl;
    h.wypisz();
    h.transpose(h2);
    h.wypisz();
    i.wypisz();
    i2.wypisz();
    i3.wypisz();
    std::cout << "wspoliniowe: " << punkt::wspolliniowe(i, i2, i3) << " dystans (i i2) : " << i.odleglosc(i2) << std::endl;
    j.wypisz();
    k.wypisz();
    l.wypisz();
    l.setName("aaaaaa");
    l.wypisz();
    return 0;
}