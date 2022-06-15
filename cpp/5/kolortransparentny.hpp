#ifndef kt_hpp
#define kt_hpp

#include <iostream>
#include "kolory.hpp"

class kolortransparentny: public kolory
{
    protected:
        int alfa;

    public:
        kolortransparentny();
        kolortransparentny(int, int, int, int);

        int getAlfa() const;

        void setAlfa(int);
        void wypisz() const;
};

#endif