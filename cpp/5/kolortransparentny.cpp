#include <iostream>
#include "kolortransparentny.hpp"

kolortransparentny::kolortransparentny() : kolory(), alfa(255) {};
kolortransparentny::kolortransparentny(int r, int g, int b, int alfa) : kolory(r, g, b), alfa(alfa)
{
    if (alfa > 255 || alfa < 0)
        throw new std::range_error("Alfa musi należeć do [0, 255]");
}

int kolortransparentny::getAlfa() const
{
    return alfa;
}

void kolortransparentny::setAlfa(int v)
{
    if (alfa > 255 || alfa < 0)
        throw new std::range_error("Alfa musi należeć do [0, 255]");
    alfa = v;
};

void kolortransparentny::wypisz() const
{
    std::cout << "r: " << r << " g: " << g << " b: "<< b << " alfa: " << alfa << std::endl;
}