#include <iostream>
#include "zmienna.hpp"

bool checkVariableName(std::string name)
{
    if (name == "" || isdigit(name[0])) return false; //empty or starts with a number
    for (int i = 0; i < (int)name.size(); i++)
    {
        if (!isalpha(name[i]) && !isdigit(name[i]) && name[i] != '_') return false;
    }
    return true;
}

zmienna::zmienna() : nazwa("_") {}

zmienna::zmienna(std::string name) : nazwa(name), wartosc(0)
{
    if (!checkVariableName(name)) 
        throw std::invalid_argument("Klucz powinien być niepustym ciągiem złożonym z liter, cyfr i znaku podkreślenia, nierozpoczynającym się od cyfry.");
}

zmienna::zmienna(std::string name, double value) : nazwa(name), wartosc(value)
{
    if (!checkVariableName(name))
        throw std::invalid_argument("Klucz powinien być niepustym ciągiem złożonym z liter, cyfr i znaku podkreślenia, nierozpoczynającym się od cyfry.");
}

std::string zmienna::get_name() const
{
    return nazwa;
};

double zmienna::get_value() const
{
    return wartosc;
};

void zmienna::change_value(double value) {
    wartosc = value;
};