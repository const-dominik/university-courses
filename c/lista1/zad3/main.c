#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int is_prime(int num)
{
    if (num <= 1) return 0;
    for (int i = 2; i<(num/2+1); i++){
        if (num % i == 0) return 0;
    }
    return 1;
}

void przedstaw(int n)
{
    if (n == 4) printf("2 2");
    for (int i = 3; i <= n/2; i += 2)
    {
        if (is_prime(i) && is_prime(n-i)) printf("%d %d ", i, n-i);
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    if (n < 4 || n>100000 || n % 2 == 1)
    {
        printf("NIEPOPRAWNA LICZBA");
        return 0;
    }
    przedstaw(n);
    return 0;
}
