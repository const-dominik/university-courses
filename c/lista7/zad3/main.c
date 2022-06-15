#include <stdio.h>
#include <stdlib.h>

void insert(int p, int x, int i, int tablica[])
{
    for (int j = i; j >= p+1; j--) tablica[j+1] = tablica[j];
    tablica[p+1] = x;
}

void sum(int p1, int p2, int tablica[])
{
    int suma = 0;
    for (int i = p1; i <= p2; i++) suma += tablica[i];
    printf("%d\n", suma);
}

void delet(int p, int i, int tablica[])
{
    for (int j = p; j < i; j++)
        tablica[j] = tablica[j+1];
}

int main()
{
    int L;
    int i = 0;
    scanf("%d\n", &L);
    int tablica[1000] = {0};
    while (i < L)
    {
        i++;
        char op;
        int l1;
        int l2 = -1;
        scanf("%c %d %d\n", &op, &l1, &l2);
        if (op == 'I') insert(l1, l2, i, tablica);
        if (op == 'S') sum(l1, l2, tablica);
        if (op == 'D') delet(l1, i, tablica);

    }
    return 0;
}
