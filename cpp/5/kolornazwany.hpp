#ifndef kn_hpp
#define kn_hpp

#include <iostream>
#include "kolortransparentny.hpp"

class kolornazwany: public kolortransparentny
{
    protected:
        std::string name;

    public:
        kolornazwany();
        kolornazwany(int, int, int, int);
        kolornazwany(int, int, int, int, std::string);

        std::string getName() const;

        void setName(std::string);
        void wypisz() const;
};

#endif