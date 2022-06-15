#include <iostream>
#include <string>
#include <cmath>
#include "liczba.hpp"

liczba::liczba(double v) : value(v) {};

double liczba::oblicz() {
    return value;
}

std::string liczba::zapis()
{
    std::string str = std::to_string (value);
    str.erase ( str.find_last_not_of('0') + 2, std::string::npos );
    return str;
}