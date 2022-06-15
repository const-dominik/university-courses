#ifndef o2a_hpp
#define o2a_hpp

#include <iostream>
#include "operator1arg.hpp"

class operator2arg: public operator1arg {
    protected:
        wyrazenie *expr2;

    //public:
        operator2arg(wyrazenie *e1, wyrazenie *e2);
};

class dodaj: public operator2arg {
    public:
        dodaj(wyrazenie *e1, wyrazenie *e2);

        double oblicz();
        std::string zapis();
        bool isLeft() override;
        int getPriority() override;
};

class odejmij: public operator2arg {
    public:
        odejmij(wyrazenie *e1, wyrazenie *e2);

        double oblicz();
        std::string zapis();
        bool isLeft() override;
        int getPriority() override;
};

class mnoz: public operator2arg {
    public:
        mnoz(wyrazenie *e1, wyrazenie *e2);

        double oblicz();
        std::string zapis();
        bool isLeft() override;
        int getPriority() override;
};

class dziel: public operator2arg {
    public:
        dziel(wyrazenie *e1, wyrazenie *e2);

        double oblicz();
        std::string zapis();
        bool isLeft() override;
        int getPriority() override;
};

class logarytm: public operator2arg {
    public:
        logarytm(wyrazenie *e1, wyrazenie *e2);

        double oblicz();
        std::string zapis();
        int getPriority() override;
};

class modulo: public operator2arg {
    public:
        modulo(wyrazenie *e1, wyrazenie *e2);

        double oblicz();
        std::string zapis();
        bool isLeft() override;
        int getPriority() override;
};

class potega: public operator2arg {
    public:
        potega(wyrazenie *e1, wyrazenie *e2);

        double oblicz();
        std::string zapis();
        bool isLeft() override;
        int getPriority() override;
};
#endif