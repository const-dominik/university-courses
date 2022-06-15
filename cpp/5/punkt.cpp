#include <iostream>
#include <cmath>
#include "punkt.hpp"

punkt::punkt(double x, double y) : x(x), y(y) {};

double punkt::odleglosc(punkt A) const
{
    double x_diff = abs(A.x - x);
    double y_diff = abs(A.y - y); 
    return sqrt(pow(x_diff, 2) + pow(y_diff, 2));
}

bool punkt::wspolliniowe(punkt a, punkt b, punkt c)
{
    return (a.x * (b.y-c.y) + b.x * (c.y-a.y) + c.x * (a.y - b.y))*0.5 == 0;
    //check if the area of triangle is equal to 0
}

void punkt::wypisz() const
{
    std::cout << "x: " << x << " y: " << y << std::endl;
}