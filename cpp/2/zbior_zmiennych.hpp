#ifndef zbior_zmiennych_hpp
#define zbior_zmiennych_hpp

#include "zmienna.hpp"

class zbior_zmiennych {
    private:
        const int n;
        zmienna *tab;
        int index;
    public:
        zbior_zmiennych(int size);
        ~zbior_zmiennych();

        void add(zmienna a);
        void remove(zmienna a);
        bool includes(zmienna a);
        double getValue(zmienna a);
        void modify(zmienna a, double new_value);
        void print();
};

#endif