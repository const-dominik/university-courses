#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include "float.h"


double a(double x) {
    return 1/(x+sqrt(x*x+2022*2022));
}

double a_fix(double x) {
    if (x <= 0) {
        return (x - sqrt(x*x+2022*2022))/(2022*2022);
    }
    return a(x);
}

double b(double x) {
    return log(x)/log(3) - 7;
}

double b_fix(double x) {
    return log(x/pow(3, 7))/log(3);
}

double c(double x) {
    return 4*cos(x)*cos(x)-3;
}

double c_fix(double x) {
    if (cos(x) <= pow(10, -10)) {
        return c(x);
    }
    return cos(3*x)/cos(x);
}

int main() {
    //     a
    // for (double x = -100; x >= -pow(10, 15); x *= 10) {
    //     printf("%f: %.30f\n", x, a(x));
    // }
    // for (double x = -100; x >= -pow(10, 15); x *= 10) {
    //     printf("(fixed a) %f: %.30f\n", x, a_fix(x));
    // }

    //     b
    // for (double x = 3000; x - pow(10, -15) > pow(3, 7); x = (x + pow(3, 7))/2) {
    //     printf("%.15f: %.40f\n", x, b(x));
    // }
    // for (double x = 3000; x - pow(10, -15) > pow(3, 7); x = (x + pow(3, 7))/2) {
    //     printf("(fixed) %.15f: %.40f\n", x, b_fix(x));
    // }

    //     c
    for (double x = pow(10, 15); x >= pow(10, -20); x /= 10) {
        printf("%.25f: %.40f\n", x, c((M_PI / 6) - x));
    }
    for (double x = pow(10, 15); x >= pow(10, -20); x /= 10) {
        printf("(fixed) %.25f: %.40f\n", x, c_fix((M_PI / 6) - x));
    }

    return 0;
}