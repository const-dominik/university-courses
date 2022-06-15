#ifndef o1a_hpp
#define o1a_hpp

#include <iostream>
#include "wyrazenie.hpp"

class operator1arg: public wyrazenie {
    protected:
        wyrazenie *expr;
        
   // public:
        operator1arg(wyrazenie* expr);
};

class sin2: public operator1arg {
    public:
        sin2(wyrazenie *expr);

        std::string zapis();
        double oblicz();
};

class cos2: public operator1arg {
    public:
        cos2(wyrazenie *expr);

        std::string zapis();
        double oblicz();
};

class exp2: public operator1arg {
    public:
        exp2(wyrazenie *expr);

        std::string zapis();
        double oblicz();
};

class ln2: public operator1arg {
    public:
        ln2(wyrazenie *expr);

        std::string zapis();
        double oblicz();
};

class bezwzgl: public operator1arg {
    public:
        bezwzgl(wyrazenie *expr);

        std::string zapis();
        double oblicz();
};

class przeciw: public operator1arg {
    public:
        przeciw(wyrazenie *expr);

        std::string zapis();
        double oblicz();
};

class odwrot: public operator1arg {
    public:
        odwrot(wyrazenie *expr);

        std::string zapis();
        double oblicz();
};
#endif