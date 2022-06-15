typedef struct {
    int licznik;
    int mianownik;
} Ulamek;

int nwd(int a, int b);
int nww(int a, int b);
Ulamek* nowy_ulamek(int num, int denom);
void show(Ulamek *u);
Ulamek* dodawanie_1(Ulamek* u1, Ulamek* u2);
Ulamek* dodawanie_2(Ulamek* u1, Ulamek* u2);
Ulamek* odejmowanie_1(Ulamek* u1, Ulamek* u2);
Ulamek* odejmowanie_2(Ulamek* u1, Ulamek* u2);
Ulamek* mnozenie_1(Ulamek* u1, Ulamek* u2);
Ulamek* mnozenie_2(Ulamek* u1, Ulamek* u2);
Ulamek* dzielenie_1(Ulamek* u1, Ulamek* u2);
Ulamek* dzielenie_2(Ulamek* u1, Ulamek* u2);
