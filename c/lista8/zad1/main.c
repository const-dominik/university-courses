//Dominik Kiełbowicz, 329595, lista 8 zad 1
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


void wypisz_plansze(int m, int plansza[m][m])
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%c", plansza[i][j] == 0 ? '.' : '*');
        printf("\n");
    }
    printf("\n");
}

int porownaj_plansze(int m, int plansza1[m][m], int plansza2[m][m])
{
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
            if (plansza1[i][j] != plansza2[i][j])
                return 0;
    return 1;
}

int ile_sasiadow(int m, int plansza[m][m], int x, int y)
{
    int suma = 0;
    for (int i = y-1; i <= y+1; i++)
        for (int j = x-1; j <= x+1; j++)
            if (i >= 0 && j >= 0 && i <= m-1 && j <= m-1)
                suma += plansza[i][j];
    suma -= plansza[y][x];
    return suma;
}

void gra_w_zycie(int m, int plansza[m][m], int max)
{
    if (max < 0) return;
    Sleep(100);
    system("cls");
    int nowa_plansza[m][m];
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
        {
            int sasiedzi = ile_sasiadow(m, plansza, j, i);
            if (sasiedzi <= 1 || sasiedzi >= 4) nowa_plansza[i][j] = 0;
            else if (sasiedzi == 3) nowa_plansza[i][j] = 1;
            else nowa_plansza[i][j] = plansza[i][j];
        }
    wypisz_plansze(m, nowa_plansza);
    if (!porownaj_plansze(m, plansza, nowa_plansza)) gra_w_zycie(m, nowa_plansza, max -1);
}

int main(int argc, char *argv[])
{
    FILE *fp;
    fp = fopen(argv[1], "r");
    int s;
    int m = atoi(argv[2]);
    int max = atoi(argv[3]);
    int plansza[m][m];
    int i = 0;
    int j = 0;
    while ((s=fgetc(fp)) != EOF)
    {
        if (s == '.') plansza[i][j] = 0;
        else if (s == '*') plansza[i][j] = 1;
        j++;
        if (s == '\n')
        {
            i++;
            j=0;
        }
    }
    wypisz_plansze(m, plansza);
    gra_w_zycie(m, plansza, max);
    fclose(fp);
    return argc;
}
