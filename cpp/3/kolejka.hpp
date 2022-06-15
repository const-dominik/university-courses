#ifndef KOLEJKA_HPP
#define KOLEJKA_HPP

#include <iostream>

class kolejka {
    private:
        int size, start, count;
        std::string *tab;

    public:
        kolejka();
        kolejka(int pojemnosc);
        kolejka(std::initializer_list<std::string>);
        kolejka(const kolejka &);
        kolejka(kolejka &&);
        ~kolejka();

        kolejka & operator=(const kolejka &);
        kolejka & operator=(kolejka &&);
        void wstaw(std::string text);
        std::string usun();
        std::string zprzodu() const;
        int dlugosc() const;
        bool isEmpty() const;
        bool isFull() const;
        void printQueue() const;
};
#endif