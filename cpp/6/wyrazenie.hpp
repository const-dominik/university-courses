#ifndef wyr_hpp
#define wyr_hpp

#include <iostream>

class wyrazenie {
    public:
        virtual double oblicz() = 0;
        virtual std::string zapis() = 0;

        virtual int getPriority();
        virtual bool isLeft();
};
#endif