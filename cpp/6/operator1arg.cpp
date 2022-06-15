#include <cmath>
#include "operator1arg.hpp"

operator1arg::operator1arg(wyrazenie *expr)
{
    this->expr = expr;
}

sin2::sin2(wyrazenie *expr) : operator1arg(expr) {};
double sin2::oblicz()
{
    return std::sin(expr->oblicz());
}

std::string sin2::zapis()
{
    return "sin(" + expr->zapis() + ")";
}

cos2::cos2(wyrazenie *expr) : operator1arg(expr) {};
double cos2::oblicz()
{
    return std::cos(expr->oblicz());
}

std::string cos2::zapis()
{
    return "cos(" + expr->zapis() + ")";
}

exp2::exp2(wyrazenie *expr) : operator1arg(expr) {};
double exp2::oblicz()
{
    return std::exp(expr->oblicz());
}

std::string exp2::zapis()
{
    return "exp(" + expr->zapis() + ")";
}

ln2::ln2(wyrazenie *expr) : operator1arg(expr) {};
double ln2::oblicz()
{
    return std::log(expr->oblicz());
}

std::string ln2::zapis()
{
    return "ln(" + expr->zapis() + ")";
}

bezwzgl::bezwzgl(wyrazenie *expr) : operator1arg(expr) {};
double bezwzgl::oblicz()
{
    return std::abs(expr->oblicz());
}

std::string bezwzgl::zapis()
{
    return "|" + expr->zapis() + "|";
}

przeciw::przeciw(wyrazenie *expr) : operator1arg(expr) {};
double przeciw::oblicz()
{
    return (-1)*expr->oblicz();
}

std::string przeciw::zapis()
{
    return "-(" + expr->zapis() + ")";
}

odwrot::odwrot(wyrazenie *expr) : operator1arg(expr) {};
double odwrot::oblicz()
{
    return 1.0 / expr->oblicz();
}

std::string odwrot::zapis()
{
    return "(1/" + expr->zapis() + ")";
}
