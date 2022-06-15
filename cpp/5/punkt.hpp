#ifndef pkt_hpp
#define pkt_hpp

#include <iostream>

class punkt
{
    protected:
        double x;
        double y;

    public:
        punkt(double = 0, double = 0);

        double odleglosc(punkt A) const;
        static bool wspolliniowe(punkt a, punkt b, punkt c);

        void wypisz() const;
};

#endif