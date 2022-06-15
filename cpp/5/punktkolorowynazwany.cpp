#include <iostream>
#include "punktkolorowynazwany.hpp"

punktkolorowynazwany::punktkolorowynazwany(double x, double y, kolortransparentny kolor, std::string nazwa) : punkt(x, y), punktkolorowy(x, y, kolor), punktnazwany(x, y, nazwa) {};

void punktkolorowynazwany::wypisz() const
{
    punkt::wypisz();
    kolor.wypisz();
    std::cout << "nazwa: " << name << std::endl;
} 