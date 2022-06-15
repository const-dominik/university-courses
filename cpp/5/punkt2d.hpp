#ifndef pkt2d_hpp
#define pkt2d_hpp

#include "punkt.hpp"
#include "wektor2d.hpp"

class punkt2d: public punkt
{
    public:
        punkt2d(double = 0, double = 0);

        void transpose(wektor2d);
};

#endif