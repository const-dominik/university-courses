#include <iostream>
#include "kolory.hpp"

bool isColorInRange(int v) {
    return v >= 0 && v <= 255;
}

kolory::kolory() : r(0), g(0), b(0) {};
kolory::kolory(int r, int g, int b) : r(r), g(g), b(b) {
    if (!isColorInRange(r) || !isColorInRange(g) || !isColorInRange(b))
        throw new std::range_error("Składowa musi być z przedziału [0, 255]");
}

int kolory::getR() const
{
    return r;
}

int kolory::getG() const
{
    return g;
}

int kolory::getB() const
{
    return b;
}

void kolory::setR(int v)
{
    if (!isColorInRange(v))
        throw new std::range_error("Składowa musi być z przedziału [0, 255]");
    r = v;
}

void kolory::setG(int v)
{
    if (!isColorInRange(v))
        throw new std::range_error("Składowa musi być z przedziału [0, 255]");
    g = v;
}

void kolory::setB(int v)
{
    if (!isColorInRange(v))
        throw new std::range_error("Składowa musi być z przedziału [0, 255]");
    b = v;
}

void kolory::darken(float p)
{
    if (p > 1 || p < 0)
        throw new std::range_error("Skalar musi należeć do przedziału [0, 1]");
    r *= p;
    g *= p;
    b *= p;
}

void kolory::lighten(float p)
{
    if (p > 1 || p < 0)
        throw new std::range_error("Skalar musi należeć do przedziału [0, 1]");
    r = 255 - (p * (255 - r));
    g = 255 - (p * (255 - g));
    b = 255 - (p * (255 - b));
}

float kolory::sumColor(kolory rgb)
{
    return (rgb.r + rgb.g + rgb.b)/3.0;
}

void kolory::wypisz() const
{
    std::cout << "r: " << r << " g: " << g << " b: "<< b << std::endl;
}