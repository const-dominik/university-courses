#ifndef stala_hpp
#define stala_hpp

#include <iostream>
#include "wyrazenie.hpp"

class stala: public wyrazenie {
    protected:
        double value;
};

class pi: public stala {
    public:
        pi();

        double oblicz();
        std::string zapis();
};

class e: public stala {
    public:
        e();

        double oblicz();
        std::string zapis();
};

class fi: public stala {
    public:
        fi();

        double oblicz();
        std::string zapis();
};

#endif