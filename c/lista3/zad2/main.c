//Dominik Kielbowicz, 329595, lista3 zad2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int porownaj(char s1[], char s2[])
{
    int i = 0;
    while (s1[i])
    {
        if (s1[i] < s2[i]) return -1;
        if (s1[i] > s2[i]) return 1;
        i++;
    }
    if (s2[i]) return -1;
    return 0;
}

void sort(char *t[], int n)
{
        for (int i = 1; i < n; i++)
        {
            int lastIndex = n-i;
            int najwIndex = lastIndex;
            for (int k = 1; k < lastIndex; k++)
                if (porownaj(t[k], t[najwIndex]) == 1)
                    najwIndex = k;
            if (najwIndex == lastIndex) continue;
            char *temp = t[najwIndex];
            t[najwIndex] = t[lastIndex];
            t[lastIndex] = temp;
        }
}

void sortuj(char *t[],int n)
{
    for (int i = 1; i < n; i++)
        for (int j = 0; j < (signed)strlen(t[i]); j++)
        {
            int lastIndex = strlen(t[i])-j-1;
            int najwIndex = lastIndex;
            for (int k = 0; k < lastIndex; k++)
                if (t[i][k] > t[i][najwIndex])
                    najwIndex = k;
            if (najwIndex == lastIndex) continue;
            char temp = t[i][najwIndex];
            t[i][najwIndex] = t[i][lastIndex];
            t[i][lastIndex] = temp;
        }
    sort(t, n);
}

void wypisz(char *t[], int n)
{
    for (int i = 1; i < n; i++) printf("%s \n", t[i]);
}

int main(int argC, char* argV[])
{
    sortuj(argV,argC);
    wypisz(argV, argC);

    return 0;
}

