#include <iostream>
#include <cmath>

double f(double x) {
    return 4044.0 * (sqrt(pow(x, 13) + 1) - 1)/pow(x, 13);
}

double y(double x) {
    if (x == 0) return 1.0;
    if (x == 1) return -1.0/7.0;
    return 146.0/7.0*y(x-1)+ 3*y(x-2);
}

double I(int n) {
    if (n == 0) return log(2023.0/2022.0);
    return 1.0/n - 2022.0*I(n-1);
}


int main()
{
    for (double i = 1; i <= 20; i++) {
        printf("%.10f: %.20f\n", pow(10, -i), f(pow(10, -i)));
    }
    return 0;
}