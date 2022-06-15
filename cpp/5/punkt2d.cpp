#include "punkt2d.hpp"

punkt2d::punkt2d(double x, double y) : punkt(x, y) {};

void punkt2d::transpose(wektor2d u)
{
    x += u.x;
    y += u.y;
}