#include <iostream>
#include <vector>
#include <utility>
#include "zmienna.hpp"

std::vector<std::pair<std::string, double>> zmienna::zmienne;

zmienna::zmienna(std::string nazwa) : name(nazwa) {};

double zmienna::oblicz()
{
    for (int i = 0; i < (int)zmienne.size(); i++)
            if (zmienne[i].first == name)
                return zmienne[i].second;
    throw new std::range_error("brak wartościowania dla zadanej zmiennej");
}

std::string zmienna::zapis()
{
    return name;
}
    
void zmienna::add(std::string name, double v)
{
    for (int i = 0; i < (int)zmienne.size(); i++)
        if (zmienne[i].first == name)
        {
            zmienne[i].second = v;
            return;
        }
    zmienne.push_back(std::make_pair(name, v));
    //modify if already in vector, add otherwise
}

void zmienna::remove(std::string name)
{
    for (int i = 0; i < (int)zmienne.size(); i++)
        if (zmienne[i].first == name)
        {
            zmienne.erase(zmienne.begin() + i);
            return;
        }
}

double zmienna::get(std::string name)
{
    for (int i = 0; i < (int)zmienne.size(); i++)
        if (zmienne[i].first == name)
            return zmienne[i].second;
    throw new std::range_error("brak wartościowania dla zadanej zmiennej");
}