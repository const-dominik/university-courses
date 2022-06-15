#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void convertNumToAnyBase(int num, int base, int tab[])
{
    int i = 0;
    while (num > 0)
    {
        tab[i] = num % base;
        num /= base;
        i++;
    }
}

int anyToDec(int base, int length, int tab[])
{
    int dec = 0;
    int power = 1;
    for (int i = length - 1; i >= 0; i--)
    {
        dec += tab[i] * power;
        power*=base;
    }
    return dec;
}

int main()
{
    srand(0);
    int B, L, N = -1, M;
    scanf("%d %d %d", &B, &L, &N);
    M = B;
    for (int i = 1; i < L; i++) M *= B;
    if (N == -1) N = M;
    int num[L];
    for (int i = 0; i < N; i++)
    {
        for (int i = 0; i < L; i++) num[i] = 0;
        convertNumToAnyBase(i%M, B, num);
        int decimal = anyToDec(B, L, num);
        for (int i = 0; i < N; i++) printf("%c", i == decimal%N ? 'x' : '.');
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < N; i++)
    {
        int random = rand() % N;
        for (int i = 0; i < N; i++) printf("%c", i == random ? 'x' : '.');
        printf("\n");
    }
    return 0;
}
