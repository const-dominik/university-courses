//Dominik Kielbowicz, nr indeksu 329595, lista 1 zadanie 1
#include <stdio.h>
#include <stdlib.h>

int is_perfect(int num)
{
    int suma = 0;
    for (int i = 1; i <= num/2; i++)
    {
        if (num % i == 0) suma += i;
    }
    return suma == num;
}

int main()
{
    for (int i = 1; i <= 100000; i++)
    {
        if (is_perfect(i)) printf("%d ", i);
    }
    return 0;
}
