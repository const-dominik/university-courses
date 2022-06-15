#include "punktkolorowy.hpp"
#include "punkt.hpp"

punktkolorowy::punktkolorowy(double x, double y, kolortransparentny kolor) : punkt(x, y), kolor(kolor) {};

void punktkolorowy::wypisz() const
{
    punkt::wypisz();
    kolor.wypisz();
}