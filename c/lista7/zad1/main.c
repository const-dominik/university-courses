//Dominik Kiełbowicz, 329595, lista7 zad1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

struct dzis {
    int dzien_tygodnia;
    int dzien_miesiaca;
    int miesiac;
    int rok;
};

int which_day(char day[])
{
    if (!strcmp(day, "niedziela")) return 0;
    if (!strcmp(day, "poniedzialek") || !strcmp(day, "poniedziałek")) return 1;
    if (!strcmp(day, "wtorek")) return 2;
    if (!strcmp(day, "sroda") || !strcmp(day, "środa")) return 3;
    if (!strcmp(day, "czwartek")) return 4;
    if (!strcmp(day, "piatek") || !strcmp(day, "piątek")) return 5;
    if (!strcmp(day, "sobota")) return 6;
    return -1;
}

int dni_w_miesiacu(int mies, int rok)
{
    if (mies == 2) return rok % 4 == 0 ? 29 : 28;
    int ti[7] = {1, 3, 5, 7, 8, 10, 12};
    for (int i = 0; i < 7; i++) if (ti[i] == mies) return 31;
    return 30;
}

int czy_szukana_data(struct dzis dzien, int szukane[], int miesiac)
{
    return dzien.dzien_tygodnia == szukane[0] && dzien.dzien_miesiaca == szukane[1] && (miesiac ? dzien.miesiac == szukane[2] : 1);
}

void dodaj_dzien(struct dzis *dzien)
{
    if (dzien->dzien_tygodnia == 6) dzien->dzien_tygodnia = 0;
    else dzien->dzien_tygodnia++;

    int dni = dni_w_miesiacu(dzien->miesiac, dzien->rok);
    if (dzien->dzien_miesiaca == dni) {
        dzien->dzien_miesiaca = 1;
        if (dzien->miesiac == 12) {
            dzien->miesiac = 1;
            dzien->rok++;
        } else dzien->miesiac++;
    } else dzien->dzien_miesiaca++;
}

void data(int szukane[], int miesiac)
{
    struct dzis dzien;
    time_t now;
    time(&now);
    struct tm *tm = localtime(&now);
    dzien.dzien_tygodnia = tm->tm_wday;
    dzien.dzien_miesiaca = tm->tm_mday;
    dzien.miesiac = tm->tm_mon+1;
    dzien.rok = tm->tm_year + 1900;
    int dni = 0;
    int dni_max = 365*100;
    while (!czy_szukana_data(dzien, szukane, miesiac))
    {
        dodaj_dzien(&dzien);
        dni++;
    }
    if (dni > dni_max) printf("nie ma takiego dnia przez najblizsze 100 lat");
    else printf("%d/%d/%d", dzien.dzien_miesiaca, dzien.miesiac, dzien.rok);
}

int main(int argc, char *argv[])
{
    for (int i = 0; i < (signed)strlen(argv[1]); i++) argv[1][i] = tolower(argv[1][i]);
    int szukane[3] = { which_day(argv[1]), atoi(argv[2]), -1 };
    if (argc == 4) szukane[2] = atoi(argv[3]);
    data(szukane, argc == 4);
    return 0;
}
