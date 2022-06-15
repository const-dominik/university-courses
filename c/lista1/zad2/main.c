//Dominik Kielbowicz, nr indeksu 329595, lista 1 zadanie 2
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int is_prime(int num)
{
    if (num <= 1) return 0;
    for (int i = 2; i<(num/2+1); i++){
        if (num % i == 0) return 0;
    }
    return 1;
}

int najwiekszy_dzielnik(int num)
{
    if (is_prime(num)) return num;
    for (int i = (signed)sqrt(num); i > 1; i--)
        if (num % i == 0 && is_prime(i))
            return i;
    return 0;
}

int main()
{
    unsigned n;
    printf("podaj liczbe ");
    scanf("%u",&n);
    printf("%d", najwiekszy_dzielnik(n));
    return 0;
}
