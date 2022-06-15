#include <iostream>
#include "kolornazwany.hpp"

kolornazwany::kolornazwany() : kolortransparentny(), name("") {};
kolornazwany::kolornazwany(int r, int g, int b, int alfa) : kolortransparentny(r, g, b, alfa) {};
kolornazwany::kolornazwany(int r, int g, int b, int alfa, std::string nazwa) : kolortransparentny(r, g, b, alfa), name(nazwa)
{
    for (int i = 0; i < (int)nazwa.size(); i++)
    {
        if (!isalpha(nazwa[i]))
            throw new std::invalid_argument("Nazwa musi składać się tylko z liter.");
    }
};


std::string kolornazwany::getName() const
{
    return name;
}

void kolornazwany::setName(std::string v)
{
    for (int i = 0; i < (int)v.size(); i++)
        if (!isalpha(v[i]))
            throw new std::invalid_argument("Nazwa musi składać się tylko z liter.");
    name = v;
};

void kolornazwany::wypisz() const
{
    std::cout << "r: " << r << " g: " << g << " b: "<< b << " alfa: " << alfa << " nazwa: " << name << std::endl;
}