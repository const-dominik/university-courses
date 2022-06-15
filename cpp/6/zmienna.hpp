#ifndef zmienna_hpp
#define zmienna_hpp

#include <iostream>
#include <vector>
#include <utility>
#include "wyrazenie.hpp"

class zmienna: public wyrazenie {
    private:
        std::string name;
        static std::vector<std::pair<std::string, double>> zmienne;

    public:
        double oblicz();
        std::string zapis();

        static void add(std::string, double);
        static void remove(std::string);
        static double get(std::string);

        zmienna(std::string);
};

#endif