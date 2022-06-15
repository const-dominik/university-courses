#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define lli long long int

lli nwd(lli a, lli b)
{
    while (a != b)
    {
        if (a > b) a -= b;
        else b -= a;
    }
    return a;
}

lli nww(lli a, lli b)
{
    return a*b/nwd(a,b);
}

lli nwde(lli a, lli b)
{
    lli p = 1;
    lli q = 0;
    lli r = 0;
    lli s = 1;
    while (b != 0)
    {
        lli c = a % b;
        lli dz = a / b;
        a = b;
        b = c;

        lli temp1 = r;
        lli temp2 = s;
        r = p - dz*r;
        s = q - dz*s;
        p = temp1;
        q = temp2;
    }
    printf("%lld %lld %lld\n", a, p, q);
    return p;
}

void privpub(int p, int q, int t)
{
    lli n = p*q;
    lli l = nww(p-1, q-1);
    lli e = 3;
    for (; nwd(e, l) != 1; e++);
    lli d = nwde(e, l);
    printf("%lli %lli\n", n, t == 0 ? e : d);
}

int main()
{
    int M;
    scanf("%d\n", &M);
    while (M > 0)
    {
        char polecenie[10];
        lli a, b;
        scanf("%s %lld %lld\n", polecenie, &a, &b);
        if (strcmp(polecenie, "GCD") == 0) printf("%lld\n", nwd(a, b));
        if (strcmp(polecenie, "LCM") == 0) printf("%lld\n", nww(a, b));
        if (strcmp(polecenie, "GCDE") == 0) nwde(a, b);
        //if (strcmp(polecenie, "POWMOD") == 0) printf("%lld\n", powmod(a, b, c));
        if (strcmp(polecenie, "PRIVKEY") == 0) privpub(a, b, 1);
        if (strcmp(polecenie, "PUBKEY") == 0) privpub(a, b, 0);
        M--;
    }
    return 0;
}
