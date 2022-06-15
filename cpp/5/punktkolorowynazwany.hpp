#ifndef pktkn_hpp
#define pktkn_hpp

#include <iostream>
#include "punktkolorowy.hpp"
#include "punktnazwany.hpp"

class punktkolorowynazwany: public punktkolorowy, public punktnazwany
{
    public:
        punktkolorowynazwany(double, double, kolortransparentny, std::string);

    void wypisz() const;
};

#endif