#ifndef wektor3d_hpp
#define wektor3d_hpp

#include "wektor2d.hpp"

class wektor3d: public wektor2d
{
    public:
        double z;
        wektor3d(double = .0, double = .0, double = .0);
};

#endif