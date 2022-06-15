#include <iostream>
#include <cmath>
#include "operator2arg.hpp"

operator2arg::operator2arg(wyrazenie *expr1, wyrazenie *expr2) : operator1arg(expr1)
{
    this->expr2 = expr2;
}

dodaj::dodaj(wyrazenie *expr1, wyrazenie *expr2) : operator2arg(expr1, expr2) {};
double dodaj::oblicz()
{
    return expr->oblicz() + expr2->oblicz();
}

bool dodaj::isLeft()
{
    return true;
}

int dodaj::getPriority()
{
    return 5;
}

std::string dodaj::zapis()
{
    std::string left, right;
    left = expr->zapis();
    right = expr2->zapis();
    return "(" + left + " + " + right + ")";
}

odejmij::odejmij(wyrazenie *expr1, wyrazenie *expr2) : operator2arg(expr1, expr2) {};
double odejmij::oblicz()
{
    return expr->oblicz() - expr2->oblicz();
}

bool odejmij::isLeft()
{
    return true;
}

int odejmij::getPriority()
{
    return 5;
}

std::string odejmij::zapis()
{
    std::string left, right;
    left = expr->zapis();
    right = expr2->zapis();
    return "(" + left + " - " + right + ")";
}

mnoz::mnoz(wyrazenie *expr1, wyrazenie *expr2) : operator2arg(expr1, expr2) {};
double mnoz::oblicz()
{
    return expr->oblicz() * expr2->oblicz();
}

bool mnoz::isLeft()
{
    return true;
}

int mnoz::getPriority()
{
    return 6;
}

std::string mnoz::zapis()
{
    return expr->zapis() + " * " + expr2->zapis();
}

dziel::dziel(wyrazenie *expr1, wyrazenie *expr2) : operator2arg(expr1, expr2) {};
double dziel::oblicz()
{
    return expr->oblicz() / expr2->oblicz();
}

bool dziel::isLeft()
{
    return true;
}

int dziel::getPriority()
{
    return 6;
}

std::string dziel::zapis()
{
    std::string left, right;
    left = expr->zapis();
    right = expr2->zapis();
    return "(" + left + " / " + right + ")";
}

logarytm::logarytm(wyrazenie *expr1, wyrazenie *expr2) : operator2arg(expr1, expr2) {};
double logarytm::oblicz()
{
    return std::log(expr2->oblicz()) / std::log(expr->oblicz());
}

int logarytm::getPriority()
{
    return 7;
}

std::string logarytm::zapis()
{
    return  "log(" + expr->zapis() + ", " + expr2->zapis() + ")";
}

modulo::modulo(wyrazenie *expr1, wyrazenie *expr2) : operator2arg(expr1, expr2) {};
double modulo::oblicz()
{
    return std::fmod(expr->oblicz(), expr2->oblicz());
}

bool modulo::isLeft()
{
    return true;
}

int modulo::getPriority()
{
    return 6;
}

std::string modulo::zapis()
{
    std::string left, right;
    left = expr->zapis();
    right = expr2->zapis();
    return left + " % " + right;
}

potega::potega(wyrazenie *expr1, wyrazenie *expr2) : operator2arg(expr1, expr2) {};
double potega::oblicz()
{
    return std::pow(expr->oblicz(), expr2->oblicz());
}

bool potega::isLeft()
{
    return false;
}

int potega::getPriority()
{
    return 6;
}

std::string potega::zapis()
{
    std::string left, right;
    left = expr->zapis();
    right = expr2->zapis();
    return left + "^" + right;
}