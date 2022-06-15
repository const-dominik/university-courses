//Dominik Kiełbowicz, 329595, lista 5 zadanie 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void wypisz(int n)
{
    char do20[20][20] = {"zero", "jeden", "dwa", "trzy", "cztery", "pięć", "sześć", "siedem", "osiem", "dziewięć", "dziesięć", "jedenaście",
    "dwanaście", "trzynaście", "czternaście", "piętnaście", "szesnaście", "siedemnaście", "osiemnaście", "dziewiętnaście" };
    char dziesiatki[8][20] = {"dwadzieścia", "trzydzieści", "czterdzieści", "pięćdziesiąt", "sześćdziesiąt", "siedemdziesiąt", "osiemdziesiąt", "dziewięćdziesiąt"};
    char setki[9][20] = {"sto", "dwieście", "trzysta", "czterysta", "pięćset", "sześćset", "siedemset", "osiemset", "dziewięćset"};
    char tysiace[9][20] = {"tysiąc", "tysiące", "tysiące", "tysiące", "tysięcy", "tysięcy", "tysięcy", "tysięcy", "tysięcy"};
    if (n < 20) printf("%s ", do20[n]);
    else if (n < 100)
    {
        printf("%s ", dziesiatki[n/10-2]);
        if (n%10) wypisz(n%10);
    }
    else if (n < 1000)
    {
        printf("%s ", setki[n/100-1]);
        if (n%100) wypisz(n%100);
    }
    else if (n < 1000000)
    {
        if (n/1000 > 1) wypisz (n/1000);
        printf("%s ", tysiace[n/1000%10-1]);
        if (n%1000) wypisz(n%1000);
    }
    else if (n <= 9000000)
    {
        if (n/1000000 > 1) wypisz(n/1000000);
        printf("%s ", n/1000000 > 1 ? "milionów" : "milion");
        if (n%1000000) wypisz(n%1000000);
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    wypisz(n);
    return 0;
}
