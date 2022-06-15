//Dominik Kiełbowicz, 329595, lista 9 zad 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int ktore_stulecie(int a)
{
    if (a == 0 || a == 1) return 19;
    if (a == 2 || a == 3) return 20;
    if (a == 4 || a == 5) return 21;
    if (a == 6 || a == 7) return 22;
    if (a == 8 || a == 9) return 18;
    return 0;
}

void data_urodzenia(int pesel[])
{
    int stulecie = ktore_stulecie(pesel[2]);
    char *dni[31] = {
        "pierwszy", "drugi", "trzeci", "czwarty", "piąty", "szósty", "siódmy",
        "ósmy", "dziewiąty", "dziesiąty", "jedenasty", "dwunasty", "trzynasty", "czternasty",
        "piętnasty", "szesnasty", "siedemnasty", "osiemnasty", "dziewiętnasty", "dwudziesty",
        "dwudziesty pierwszy", "dwudziesty drugi", "dwudziesty trzeci", "dwudziesty czwarty",
        "dwudziesty piąty", "dwudziesty szósty", "dwudziesty siódmy", "dwudziesty ósmy",
        "dwudziesty dziewiąty", "trzydziesty", "trzydziesty pierwszy"
    };
    char *miesiace[12] = {
        "stycznia", "lutego", "marca", "kwietnia", "maja", "czerwca",
        "lipca", "sierpnia", "września", "października", "listopada", "grudnia"
    };
    int dzien = pesel[4]*10 + pesel[5] - 1;
    int miesiac = pesel[3] + (pesel[2] % 2 == 0 ? 0 : 10) - 1;
    printf("%s %s %d%d%d\n", dni[dzien], miesiace[miesiac], stulecie, pesel[0], pesel[1]);
}

void liczba_porzadkowa(int pesel[])
{
    for (int i = 6; i < 10; i++) printf("%d", pesel[i]);
}

void plec(int pesel[])
{
    printf("\n%s\n", pesel[9] % 2 == 0 ? "kobieta" : "mężczyzna");
}

int cyfra_kontrolna(int pesel[])
{
    int suma = 0;
    int wagi[4] = { 1, 3, 7, 9 };
    for (int i = 0; i < 10; i++) suma += (pesel[i]*wagi[i%4])%10;
    int kontrolna = 10 - suma%10;
    if (kontrolna == pesel[10])
    {
        printf("Cyfra kontrolna jest poprawna.\n");
        return 1;
    }
    else
    {
        printf("Cyfra kontrolna jest niepoprawna.\n");
        return 0;
    }
    return -1;
}

void wypisz_pesel(int pesel[])
{
    if (cyfra_kontrolna(pesel))
    {
        data_urodzenia(pesel);
        liczba_porzadkowa(pesel);
        plec(pesel);
    }
}

int main()
{
    char pesel[11];
    scanf("%s", &pesel[0]);
    int pesel_l[11];
    for (int i = 0; i < 11; i++) pesel_l[i] = (int)(pesel[i] - '0');
    wypisz_pesel(pesel_l);
    return 0;
}
