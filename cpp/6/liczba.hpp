#ifndef liczba_hpp
#define liczba_hpp

#include <iostream>
#include "wyrazenie.hpp"

class liczba: public wyrazenie {
    private:
        double value;

    public:
        double oblicz();
        std::string zapis();

        liczba(double);
};

#endif