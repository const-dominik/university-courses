//Dominik Kielbowicz, 329525, lista 2 zad. 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void wypisztablice(int tab[3][82])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; 0 != tab[i][j]; j++)
            putchar(tab[i][j]);
}

void a()
{
    int p;
    unsigned long g, h=0;
    while ((p=getchar()) != EOF)
    {
        h = (h << 4) + p;
        g = (h & 0xF0000000);
        if (g) h = h^(g | (g >> 24));
    }
    printf("%lu", (h % 7919 + 1));
}

void b()
{
    int znaki = 0;
    int wiersze=0;
    int p;
    while ((p=getchar()) != EOF)
    {
        if (p == '\n')
            wiersze++;
        znaki++;
    }
    printf("znaki: %d, wiersze: %d\n", znaki, wiersze);
}

void c()
{
    int tab[3][82] = {{0}, {0}, {0}};
    int p;
    int i = 0;
    int linia = 0;
    while ((p=getchar()) != EOF)
    {
        int k = linia % 3;
        if (i == 0) memset(tab[k], 0, 82);
        tab[k][i] = p;
        i++;
        if (p == '\n')
        {
            linia++;
            i = 0;
        }
        if (linia == 3 && i == 0)
            wypisztablice(tab);
    }
    wypisztablice(tab);
}

void program(char n)
{
    if (n == 'a') a();
    else if (n == 'b') b();
    else if (n == 'c') c();
}

 int main(int argc, char *argv[])
{
    program(*(argv[1]));
    return argc;
}
