#include <stdio.h>
#include <stdlib.h>
#include "ulamek.h"

int main()
{
    Ulamek *u1, *u2;
    u1 = nowy_ulamek(7, 15);
    u2 = nowy_ulamek(3, 8);
    show(u1);
    show(u2);

    printf("\ntworzenie nowego ułamka:\n");
    printf("u1: "); show(u1); printf("u2: "); show(u2);
    printf("dodawanie: "); show(dodawanie_1(u1, u2));
    printf("odejmowanie: "); show(odejmowanie_1(u1, u2));
    printf("mnozenie: "); show(mnozenie_1(u1, u2));
    printf("dzielenie: "); show(dzielenie_1(u1, u2));

    printf("\nzmiana drugiego ułamka:\n");
    printf("u1: "); show(u1); printf("u2: "); show(u2);
    printf("dodawanie: "); dodawanie_2(u1, u2); show(u2);
    printf("u1: "); show(u1); printf("u2: "); show(u2);
    printf("odejmowanie: "); odejmowanie_2(u1, u2); show(u2);
    printf("u1: "); show(u1); printf("u2: "); show(u2);
    printf("mnozenie: "); mnozenie_2(u1, u2); show(u2);
    printf("u1: "); show(u1); printf("u2: "); show(u2);
    printf("dzielenie: "); dzielenie_2(u1, u2); show(u2);
    printf("u1: "); show(u1); printf("u2: "); show(u2);

    return 0;
}
