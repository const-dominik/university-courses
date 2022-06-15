#include <stdio.h>
#include <stdlib.h>

void wypiszKwadrat(int n)
{
    char tab[n][n];
    int ile = n/2+1;
    for (int i = 0; i < ile; i++)
    {
        char mainC = (ile-i) % 2 == 0 ? 'o' : '#';
        for (int j = i; j <= n-i-1; j++)
        {
            tab[i][j] = mainC;
            tab[j][i] = mainC;
            tab[n-1-i][j] = mainC;
            tab[j][n-1-i] = mainC;
        }
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i == j || j == n-i-1) tab[i][j] = '#';
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%c", tab[i][j]);
        printf("\n");
    }

}

int main()
{
    int n;
    scanf("%d", &n);
    if (n % 2 == 0 || n < 1) printf("ERROR");
    wypiszKwadrat(n);
    return 0;
}
