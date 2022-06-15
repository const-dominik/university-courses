//329595, Dominik Kiełbowicz, zadanie 1
#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

vector<int64_t> rozklad(int64_t n)
{
    vector<int64_t> odp;
    if (n == -1 || n == 0 || n == 1) //rozklad tozsamy -1, 0, 1
    {
        odp.push_back(n);
        return odp;
    }

    if (n < 0) //dodanie czynnika -1 dla liczb ujemnych
    {
        odp.push_back(-1);
    }

    while (n % 2 == 0) //sprawdzenie osobno dla liczby 2
    {
        odp.push_back(2);
        n /= 2;
    }

    if (n < 0) n *= -1;

    int64_t dzielnik = 3;
    while (n != 1 && dzielnik <= sqrt(n))
    {
        while (n % dzielnik == 0)
        {
            odp.push_back(dzielnik);
            n /= dzielnik;
        }
        dzielnik += 2;
    }

    if (n != 1) // liczba pierwsza 
    {
        odp.push_back(n);   
    }

    return odp;
}

void wypisz(vector<int64_t> tab, int64_t num)
{
    cout << "Rozkład liczby " << num << ": ";
    for (int i = 0; i < (int)tab.size(); i++)
    {
        cout << tab[i] << " ";
    }
    cout << endl;
}

int main(int argc, char* argv[])
{
    if (argc == 1) 
    {
        cerr << "Nie podano żadnej liczby! Sposób poprawnego wywołania: [nazwa pliku] [liczby oddzielone znakiem spacji]";
        return 0;
    }
    for (int i = 1; i < argc; i++)
    {
        int64_t liczba = stoll(argv[i]);
        vector<int64_t> tab = rozklad(liczba);
        wypisz(tab, liczba);
    }
    return 0;
}
