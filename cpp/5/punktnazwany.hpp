#ifndef pktn_hpp
#define pktn_hpp

#include <iostream>
#include "punkt.hpp"

class punktnazwany: public virtual punkt
{
    protected:
        std::string name;

    public:
        punktnazwany(double, double, std::string = "");

        std::string getName() const;

        void setName(std::string);
        void wypisz() const;
};

#endif