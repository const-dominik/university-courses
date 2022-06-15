#ifndef kolory_hpp
#define kolory_hpp

#include <iostream>

class kolory
{
    protected:
        int r, g, b;

    public:
        kolory();
        kolory(int, int, int);

        int getR() const;
        int getG() const;
        int getB() const;

        void setR(int);
        void setG(int);
        void setB(int);

        void darken(float);
        void lighten(float);

        static float sumColor(kolory);
        void wypisz() const;
};

#endif