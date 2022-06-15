#include <iostream>
#include "wyrazenie.hpp"
#include "liczba.hpp"
#include "stala.hpp"
#include "zmienna.hpp"
#include "operator1arg.hpp"
#include "operator2arg.hpp"

int main()
{
    wyrazenie *w = new odejmij(
        new pi(),
        new dodaj(
            new liczba(2),
            new mnoz(
                new zmienna("x"),
                new liczba(7)
            )
        )
    );

    wyrazenie *w2 = new dziel(
        new mnoz(
            new odejmij(
                new zmienna("x"),
                new liczba(1.0)
            ),
            new zmienna("x")
        ),
        new liczba(2.0)
    );

    wyrazenie *w3 = new dziel(
        new dodaj(
            new liczba(3),
            new liczba(5)
        ),
        new dodaj(
            new liczba(2),
            new mnoz(
                new zmienna("x"),
                new liczba(7)
            )
        )
    );

    wyrazenie *w4 = new dodaj(
            new liczba(2),
            new odejmij(
                new mnoz(
                    new zmienna("x"),
                    new liczba(7)
                ),
                new dodaj(
                    new mnoz(
                        new zmienna("y"),
                        new liczba(3)
                    ),
                    new liczba(5)
                )
            )
    );

    wyrazenie *w5 = new dziel(
        new cos2(new mnoz(
            new dodaj(
                new zmienna("x"),
                new liczba(1)
            ),
            new pi()
        )),
        new potega(new e(),
            new potega(new zmienna("x"), new liczba(2)))
    );
    std::cout << w->zapis() << std::endl;
    std::cout << w2->zapis() << std::endl;
    std::cout << w3->zapis() << std::endl;
    std::cout << w4->zapis() << std::endl;
    std::cout << w5->zapis() << std::endl;

    zmienna::add("x", 0);
    zmienna::add("y", 0);
    std::cout << w->oblicz() << " ";
    std::cout << w2->oblicz() << " ";
    std::cout << w3->oblicz() << " ";
    std::cout << w4->oblicz() << " ";
    std::cout << w5->oblicz() << " " << std::endl << "---------" << std::endl;

    for (double i = 0; i <= 1.0; i += 0.1)
    {
        zmienna::add("x", i);
        zmienna::add("y", i);
        std::cout << w->oblicz() << " ";
    }

    std::cout << std::endl << "---------" << std::endl << w->oblicz() << " ";
    std::cout << w2->oblicz() << " ";
    std::cout << w3->oblicz() << " ";
    std::cout << w4->oblicz() << " ";
    std::cout << w5->oblicz() << " ";
}