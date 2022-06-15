//Dominik Kielbowicz, lista 2 zad 3, 329595
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int m, s, n, Ni, Wi, WiTab[1000], NiTab[1000], osoby = 0, pietro = 0, ruchy = 0, gamechanger = 1;
    scanf("%d", &m);
    scanf("%d", &s);
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &Ni, &Wi);
        NiTab[i] = Ni;
        WiTab[i] = Wi;
    }
    while (ruchy <= s)
    {
        osoby = (osoby - WiTab[pietro] < 0) ? 0 : osoby - WiTab[pietro];
        if (s == ruchy) break;
        osoby = (osoby + NiTab[pietro] > m) ? m : osoby + NiTab[pietro];
        if (pietro == n-1) gamechanger = -1;
        if (pietro == 0) gamechanger = 1;
        pietro += gamechanger;
        ruchy++;
    }
    printf("%d %d", pietro, osoby);
    return 0;
}
