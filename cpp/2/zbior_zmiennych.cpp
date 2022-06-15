#include "zmienna.hpp"
#include "zbior_zmiennych.hpp"

zbior_zmiennych::zbior_zmiennych(int size) : n(size), tab(new zmienna[size]), index(0)
{
    if (size < 1) throw std::invalid_argument("Rozmiar tablicy musi być większy od 0!");
};

zbior_zmiennych::~zbior_zmiennych()
{
    delete[] this->tab;
}

void zbior_zmiennych::add(zmienna a)
{
    if (!this->includes(a.get_name()) && this->index != this->n)
    {
        this->tab[this->index] = a;
        this->index++;
    }
}

void zbior_zmiennych::remove(zmienna a)
{
    for (int i = 0; i < this->index; i++)
    {
        if (this->tab[i].get_name() == a.get_name())
        {
            this->index--;
            for (int j = i; j < this->index; j++)
            {
                this->tab[j] = this->tab[j+1];
            }
            break;
        }
    }
}

bool zbior_zmiennych::includes(zmienna a)
{
    for (int i = 0; i < this->index; i++)
    {
        if (this->tab[i].get_name() == a.get_name()) return true;
    }
    return false;
}

double zbior_zmiennych::getValue(zmienna a)
{
    if (!this->includes(a)) throw std::invalid_argument("zbior nie zawiera zmiennej");
    double val;
    for (int i = 0; i < this->index; i++)
    {
        if (this->tab[i].get_name() == a.get_name()) 
        {
            val = this->tab[i].get_value();
            break;
        }
    }
    return val;
}

void zbior_zmiennych::modify(zmienna a, double new_value)
{
    for (int i = 0; i < this->index; i++)
    {
        if (this->tab[i].get_name() == a.get_name()) this->tab[i].change_value(new_value);
    }
}

void zbior_zmiennych::print()
{
    for (int i = 0; i < this->index; i++)
    {
        std::cout << "(" << this->tab[i].get_name() << ", " << this->tab[i].get_value() << ") ";
    }
    std::cout << std::endl;
}