#ifndef zmienna_hpp
#define zmienna_hpp

#include <iostream>

class zmienna {
    private:
        std::string nazwa;
        double wartosc;

    public:
        zmienna();
        zmienna(std::string name);
        zmienna(std::string name, double value);

        std::string get_name() const;
        double get_value() const;
        void change_value(double value);
};

#endif