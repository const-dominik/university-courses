#include <iostream>
#include <cmath>

double f(double x) {
    return 4044.0 * 1 / (sqrt(pow(x, 13) + 1) + 1);
}

int main()
{
    for (int i = 1; i <= 20; i++) {
        printf("10^-%d: %.20f\n", i, f(pow(10, -i)));
    }
    return 0;
}