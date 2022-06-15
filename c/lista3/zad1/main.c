//Dominik Kielbowicz, 329595, lista3/zad1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 1000
#define MAXLEN 80

int palindrom(int linia[MAXLEN])
{
    int length = 0;
    while (linia[length] != 0) length++;
    for (int i = 0; i < length/2; i++)
        if (linia[i] != linia[length-1-i]) return 0;
    return 1;
}

void wypisz(int tab[MAXLINES])
{
    for (int i = 0; tab[i]; i++)
        printf("%d.%c\n", i+1, tab[i]);
}

int main()
{
    int tab[MAXLINES] = {0};
    int tekst[MAXLEN] = {0};
    int p;
    int i = 0;
    int linia = 0;
    while ((p=getchar()) != EOF)
    {
        if (p == '\n')
        {
            tab[linia] = palindrom(tekst) ? '+' : '-';
            memset(tekst, 0, 80);
            linia++;
            i=0;
            continue;
        }
        if (p == ' ') continue;
        tekst[i] = p;
        i++;
    }
    wypisz(tab);
    return 0;
}
