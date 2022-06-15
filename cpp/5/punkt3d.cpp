#include <iostream>
#include <cmath>
#include "punkt3d.hpp"

punkt3d::punkt3d(double x, double y, double z) : punkt2d(x, y), z(z) {};

void punkt3d::transpose(wektor3d u)
{
    x += u.x;
    y += u.y;
    z += u.z;
}

double punkt3d::odleglosc(punkt3d A) const
{
    double x_diff = abs(A.x - x);
    double y_diff = abs(A.y - y);
    double z_diff = abs(A.z - z);
    return sqrt(pow(x_diff, 2) + pow(y_diff, 2) + pow(z_diff, 2));
}

bool punkt3d::wspolliniowe(punkt3d a, punkt3d b, punkt3d c)
{
    //A,B and C are collinear if and only if the largest of the lengths of AB,AC and BC is equal to the sum of the other two. 
    double AB = a.odleglosc(b);
    double AC = a.odleglosc(c);
    double BC = b.odleglosc(c);
    double max_val = std::max(std::max(AB, AC), BC);
    double sum_of_rest = AB+AC+BC - max_val;
    return max_val == sum_of_rest;
}

void punkt3d::wypisz() const
{
    std::cout << "x: " << x << " y: " << y << " z: " << z << std::endl;
}