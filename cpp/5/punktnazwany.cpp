#include <iostream>
#include "punktnazwany.hpp"

void checkNazwa(std::string nazwa)
{
    if ((int)nazwa.size() > 0 && !isalpha(nazwa[0]))
        throw new std::invalid_argument("Nazwa punktu musi zaczynać się od litery.");
    for (int i = 0; i < (int)nazwa.size(); i++)
        if (!isalnum(nazwa[i]))
            throw new std::invalid_argument("Nazwa musi składać się tylko z liter.");
}


punktnazwany::punktnazwany(double x, double y, std::string nazwa) : punkt(x, y), name(nazwa)
{
    checkNazwa(nazwa);    
}

std::string punktnazwany::getName() const
{
    return name;
}

void punktnazwany::setName(std::string nazwa)
{
    checkNazwa(nazwa);
    name = nazwa;
}

void punktnazwany::wypisz() const
{
    punkt::wypisz();
    std::cout << "nazwa: " << name << std::endl;
}