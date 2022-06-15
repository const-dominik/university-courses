#include <stdio.h>
#include <stdlib.h>
#include "figura.h"

int main()
{
    Figura *f1, *f2, *f3;
    f1 = new_square(1.0, -1.0, 3.0);
    f2 = new_circle(3.0, 5.1, 5.0);
    f3 = new_triangle(1.2, 3.4, 5.5, 8.0, 6.2);
    Figura *ftab[3] = { f1, f2, f3 };
    printf("pole kwadratu: %f\n", area(f1));
    printf("pole kola: %f\n", area(f2));
    printf("pole trojkata: %f\n", area(f3));
    printf("suma pol: %f\n", sum_of_areas(ftab, 3));
    printf("przed przesunieciem: \n"); show(f1);
    move(f1, 2.0, 2.0);
    printf("po przesunieciu o [2, 2]: \n"); show(f1);
    printf("wszystkie figury:\n");
    show(f1);
    show(f2);
    show(f3);
    new_triangle(1.0, 2.0, 1.0, 2.0, 4.0); //przyklad kontroli danych
    return 0;
}
