#include <stdio.h>
#include <stdlib.h>

int ile(unsigned int n)
{
    int step = 0;
    while (n != 1 || step == 1025)
    {
        if (n%2 == 0) n /= 2;
        else n = 3*n+1;
        step++;
    }
    if (step > 1024 ) return -1;
    return step;
}

int main()
{
    printf("%d", ile(17457457));
    return 0;
}
