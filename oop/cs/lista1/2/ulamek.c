#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int licznik;
    int mianownik;
} Ulamek;

int nwd(int a, int b)
{
    if (b != 0) return nwd(b, a%b);
    return a;
}

int nww(int a, int b)
{
    return a*b/nwd(a,b);
}

Ulamek* nowy_ulamek(int num, int denom)
{
    Ulamek* ulamek = malloc(sizeof(Ulamek));
    int dzielnik = nwd(num, denom);
    ulamek->licznik = num/dzielnik;
    ulamek->mianownik = denom/dzielnik;
    return ulamek;
}

void show(Ulamek *u)
{
    printf("%.4f (%d/%d)\n", (float)u->licznik/(float)u->mianownik, u->licznik, u->mianownik);
}

Ulamek* dodawanie_1(Ulamek* u1, Ulamek* u2)
{
    int nowy_mianownik = nww(u1->mianownik, u2->mianownik);
    int nowy_licznik = u1->licznik * (nowy_mianownik/u1->mianownik) + u2->licznik * (nowy_mianownik/u2->mianownik);
    Ulamek* dodane_ulamki = nowy_ulamek(nowy_licznik, nowy_mianownik);
    return dodane_ulamki;
}

Ulamek* dodawanie_2(Ulamek* u1, Ulamek* u2)
{
    int nowy_mianownik = nww(u1->mianownik, u2->mianownik);
    int nowy_licznik = u1->licznik * (nowy_mianownik/u1->mianownik) +u2->licznik * (nowy_mianownik/u2->mianownik);
    int dzielnik = nwd(nowy_licznik, nowy_mianownik);
    u2->licznik = nowy_licznik/dzielnik;
    u2->mianownik = nowy_mianownik/dzielnik;
    return u2;
}

Ulamek* odejmowanie_1(Ulamek* u1, Ulamek* u2)
{
    int nowy_mianownik = nww(u1->mianownik, u2->mianownik);
    int nowy_licznik = u1->licznik * (nowy_mianownik/u1->mianownik) - u2->licznik * (nowy_mianownik/u2->mianownik);
    Ulamek* odjete_ulamki = nowy_ulamek(nowy_licznik, nowy_mianownik);
    return odjete_ulamki;
}

Ulamek* odejmowanie_2(Ulamek* u1, Ulamek* u2)
{
    int nowy_mianownik = nww(u1->mianownik, u2->mianownik);
    int nowy_licznik = u1->licznik * (nowy_mianownik/u1->mianownik) - u2->licznik * (nowy_mianownik/u2->mianownik);
    int dzielnik = nwd(nowy_licznik, nowy_mianownik);
    u2->licznik = nowy_licznik/dzielnik;
    u2->mianownik = nowy_mianownik/dzielnik;
    return u2;
}

Ulamek* mnozenie_1(Ulamek* u1, Ulamek* u2)
{
    int nowy_mianownik = u1->mianownik * u2->mianownik;
    int nowy_licznik = u1->licznik * u2->licznik;
    Ulamek* pomnozone_ulamki = nowy_ulamek(nowy_licznik, nowy_mianownik);
    return pomnozone_ulamki;
}

Ulamek* mnozenie_2(Ulamek* u1, Ulamek* u2)
{
    int nowy_mianownik = u1->mianownik * u2->mianownik;
    int nowy_licznik = u1->licznik * u2->licznik;
    int dzielnik = nwd(nowy_licznik, nowy_mianownik);
    u2->licznik = nowy_licznik/dzielnik;
    u2->mianownik = nowy_mianownik/dzielnik;
    return u2;
}

Ulamek* dzielenie_1(Ulamek* u1, Ulamek* u2)
{
    int nowy_mianownik = u1->mianownik * u2->licznik;
    int nowy_licznik = u1->licznik * u2->mianownik;
    Ulamek* podzielone_ulamki = nowy_ulamek(nowy_licznik, nowy_mianownik);
    return podzielone_ulamki;
}

Ulamek* dzielenie_2(Ulamek* u1, Ulamek* u2)
{
    int nowy_mianownik = u1->mianownik * u2->licznik;
    int nowy_licznik = u1->licznik * u2->mianownik;
    int dzielnik = nwd(nowy_licznik, nowy_mianownik);
    u2->licznik = nowy_licznik/dzielnik;
    u2->mianownik = nowy_mianownik/dzielnik;
    return u2;
}
