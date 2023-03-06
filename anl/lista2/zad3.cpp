#include <iostream>
#include <cmath>

using namespace std;

void wypisz_mozliwosci(int signum, int c) {
    printf("signum: %d, c: %d\n", signum, c);
    for (int x = 0b10000; x < 0b100000; x+=0b00001) {
        int licznik = x;
        int mianownik = (0b100000 * pow(2, -c));
        if (licznik >= mianownik) {
            int calosci = licznik/mianownik;
            licznik = licznik % mianownik;           
            if (licznik > 0) {
                printf("%d + %d/%d\n", signum*calosci, signum*licznik, mianownik);
            } else {
                printf("%d\n", signum*calosci);
            }
        } else {
            printf("%d/%d\n", signum*licznik, mianownik);
        }
    }
}

int main()
{
    for(int c = -1; c <= 1; c++){
        wypisz_mozliwosci(-1, c);
    }
    for(int c = -1; c <= 1; c++){
        wypisz_mozliwosci(1, c);
    }
}