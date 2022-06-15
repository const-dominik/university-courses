#ifndef WIELOMIAN_HPP
#define WIELOMIAN_HPP

#include <iostream>

class wielomian
{
    private:
        int n;
        double *a;

    public:
        wielomian(int st=0, double wsp=1.0);
        wielomian(int st, const double wsp[]);
        wielomian(std::initializer_list<double> wsp);
        wielomian(const wielomian &w);
        wielomian(wielomian &&w);
        wielomian& operator= (const wielomian &w);
        wielomian& operator= (wielomian &&w);
        ~wielomian();

        friend std::istream& operator>> (std::istream &we, wielomian &w);
        friend std::ostream& operator<< (std::ostream &wy, const wielomian &w);

        friend wielomian operator+ (const wielomian &u, const wielomian &v);
        friend wielomian operator- (const wielomian &u, const wielomian &v);
        friend wielomian operator* (const wielomian &u, const wielomian &v);
        friend wielomian operator* (const wielomian &u, double c);

        wielomian& operator+= (const wielomian &v);
        wielomian& operator-= (const wielomian &v);
        wielomian& operator*= (const wielomian &v);
        wielomian& operator*= (double c);

        double operator() (double x) const;
        double operator[] (int i) const;
        double& operator[] (int i);

        int getDegree() const;
};
#endif