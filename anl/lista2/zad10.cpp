#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>


double f(int k) {
    if (k == 1) return 2.0;
    return pow(2.0, k-1) * sqrt(2.0 * (1.0 - sqrt(1.0 - pow(f(k-1) / pow(2.0, k-1), 2.0))));
}

double f_popr(int k) {
    if (k == 1) return 2.0;
    double x_k_1 = f_popr(k-1);
    return sqrt(2.0 * pow(x_k_1, 2)/ (1+sqrt(1-(pow(x_k_1/pow(2.0, k-1), 2)))));
}

int main()
{
    for (int i = 1; i <= 30; i++) {
        printf("%d: %.20f\n", i, f(i));
        printf("pi: %.20f\n", M_PI);
    }
    for (int i = 1; i <= 50; i++) {
        printf("%d: %.20f\n", i, f_popr(i));
        printf("pi: %.20f\n", M_PI);
    }
    return 0;
}