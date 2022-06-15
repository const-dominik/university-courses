#ifndef pktk_hpp
#define pktk_hpp

#include <iostream>
#include "punkt.hpp"
#include "kolortransparentny.hpp"

class punktkolorowy: public virtual punkt
{
    protected:
        kolortransparentny kolor;

    public:
        punktkolorowy(double, double, kolortransparentny);

        void wypisz() const;
};

#endif