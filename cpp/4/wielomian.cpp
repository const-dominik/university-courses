#include <iostream>
#include <cstring>
#include "wielomian.hpp"

wielomian::wielomian(int st, double wsp)
{
    n = st;
    a = new double[st+1];
    for (int i = 0; i <= n; i++) a[i] = 0;
    a[n] = wsp;
};

wielomian::wielomian(int st, const double wsp[]) : wielomian(st)
{
    for (int i = 0; i < st+1; i++)
        a[i] = wsp[i];        
}

wielomian::wielomian(std::initializer_list<double> wsp) : wielomian((int)wsp.size()-1)
{
    int index = 0;
    for (auto x : wsp)
        {
            a[index] = x;
            index++;   
        }
};

wielomian::wielomian(const wielomian &w)
{
    n = w.n;
    a = new double[n+1];
    for (int i = 0; i <= n; i++)
        a[i] = w.a[i];
};

wielomian::wielomian(wielomian &&w)
{
    n = w.n;
    a = w.a;

    w.n = 0;
    w.a = nullptr;
};

wielomian & wielomian::operator= (const wielomian &w)
{
    if (this == &w) return *this;
    this->~wielomian();
    n = w.n;
    a = new double[n+1];
    for (int i = 0; i <= n; i++)
        a[i] = w.a[i];

    return *this;
}

wielomian & wielomian::operator= (wielomian &&w)
{
    if (this == &w) return *this;
    this->~wielomian();
    n = w.n;
    a = w.a;
    
    w.n = 0;
    w.a = nullptr;

    return *this;
}

std::ostream& operator<< (std::ostream &wy, const wielomian &w)
{
    if (w.a == nullptr) return wy;
    for (int i = w.n; i >= 0; i--)
    {
        if (w.a[i] == 0)
        {
            if (i != 0 && w.a[i-1] != 0) wy << " + ";
            continue;
        }
        if (w.a[i] != 1 || i == 0) wy << w.a[i];
        if (i != 0)
        {
            if (i != 1) wy << "x^" << i;
            else wy << "x";
            if (w.a[i-1] != 0) wy << " + ";
        }
    }
    wy << "\n";
    return wy;
}

std::istream& operator>> (std::istream &we, wielomian &w)
{
    std::cout << "Podaj stopień wielomianu: "; we >> w.n;
    for (int i = 0; i <= w.n; i++)
    {
        std::cout << "Podaj współczynnik x^" << i << ": ";
        we >> w.a[i];
    };

    return we;
}

wielomian operator+ (const wielomian &u, const wielomian &v)
{
    int st = std::max(u.n, v.n);
    int min_st = std::min(u.n, v.n);
    double *wsp = new double[st+1];

    for (int i = 0; i <= min_st; i++)
        wsp[i] = u.a[i] + v.a[i];

    if (st != min_st)
        for (int i = min_st+1; i <= st; i++)
            wsp[i] = (u.n > v.n ? u.a[i] : v.a[i]);

    return wielomian(st, wsp);
}

wielomian operator- (const wielomian &u, const wielomian &v)
{
    int st = std::max(u.n, v.n);
    int min_st = std::min(u.n, v.n);
    double *wsp = new double[st+1];

    for (int i = 0; i <= min_st; i++)
        wsp[i] = u.a[i] - v.a[i];

    if (st != min_st)
        for (int i = min_st+1; i <= st; i++)
            wsp[i] = (u.n > v.n ? u.a[i] : -v.a[i]);

    return wielomian(st, wsp);
}

wielomian operator* (const wielomian &u, const wielomian &v)
{
    int st = u.n + v.n;
    double *wsp = new double[st+1];
    for (int i = 0; i <= st; i++) wsp[i] = 0;
    for (int i = 0; i <= u.n; i++)
        for (int j = 0; j <= v.n; j++)
            wsp[i+j] += u.a[i] * v.a[j];

    return wielomian(st, wsp);
}

wielomian operator* (const wielomian &u, double c)
{
    double *wsp = new double[u.n+1];
    for (int i = 0; i <= u.n; i++)
        wsp[i] = u.a[i] * c;

    return wielomian(u.n, wsp);
}

wielomian & wielomian::operator+= (const wielomian &v)
{
    // wielomian p = *this + v;
    // *this = p;

    return *this = *this + v;
}

wielomian & wielomian::operator-= (const wielomian &v)
{
    wielomian p = *this - v;
    *this = p;

    return *this;
}
    
wielomian & wielomian::operator*= (const wielomian &v)
{
    wielomian p = *this * v;
    *this = p;

    return *this;
}

wielomian & wielomian::operator*= (double c)
{
    wielomian p = *this * c;
    *this = p;

    return *this;
}

double wielomian::operator() (double x) const
{
    double value = a[n];
    for (int i = n-1; i >= 0; i--)
    {
        value = value*x + a[i];
    }

    return value;
}

double wielomian::operator[] (int i) const
{
    if (i > n || i < 0)
        throw std::range_error("index out of range");
    return a[i];
}

double& wielomian::operator[](int i)
{
    if (i > n || i < 0)
        throw std::range_error("index out of range");
    //
    return a[i];
}

int wielomian::getDegree() const
{
    return n;
}

wielomian::~wielomian()
{
    delete[] a;
}