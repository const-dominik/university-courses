//Dominik Kielbowicz, 329595, lista 4 zad 1
#include <stdio.h>
#include <stdlib.h>

void wypisz_linie(int n, char opis[])
{
    printf("%s", opis);
    for (int i = 31; i >= 0; i--)
        printf("%c", (n & (1 << i)) == 0 ? '0' : '1');
    printf(" %u \n", n);
}

void operacje(unsigned a, unsigned b)
{
    wypisz_linie(a, "        a:");
    wypisz_linie(~a, "    not a:");
    wypisz_linie(b, "        b:");
    wypisz_linie(~b, "    not b:");
    wypisz_linie(a&b, "  a and b:");
    wypisz_linie(a|b, "   a or b:");
    wypisz_linie(a^b, "  a xor b:");
    wypisz_linie(a << b, "a shift b:");
}

int main()
{
    unsigned a, b;
    scanf("%u %u", &a, &b);
    operacje(a, b);
    return 0;
}
