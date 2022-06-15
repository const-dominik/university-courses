#ifndef pkt3d_hpp
#define pkt3d_hpp

#include "punkt2d.hpp"
#include "wektor3d.hpp"

class punkt3d: public punkt2d
{
    protected:
        double z;

    public:
        punkt3d(double = 0, double = 0, double = 0);

        void transpose(wektor3d);
        double odleglosc(punkt3d A) const;
        static bool wspolliniowe(punkt3d a, punkt3d b, punkt3d c);
        void wypisz() const;
};

#endif