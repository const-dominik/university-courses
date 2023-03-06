#include <iostream>
#include <cmath>
#include "utility"

using namespace std;

pair<float, float> pierw_szkolna(float a, float b, float c) {
    float x1, x2;
    float delta = b*b-4*a*c;
    if (delta < 0) throw invalid_argument("delta < 0");
    float pierw_delta = sqrt(delta);
    x1 = (-b+pierw_delta)/(2*a);
    x2 = (-b-pierw_delta)/(2*a);
    return make_pair(x1, x2);
}

pair<float, float> pierw(float a, float b, float c) {
    float x1, x2;
    float delta = b*b-4*a*c;
    if (delta < 0) throw invalid_argument("delta < 0");
    float pierw_delta = sqrt(delta);
    if (b <= 0) { 
        x1 = (-b + pierw_delta)/(2*a);
    } else {
        x1 = -(pierw_delta+b)/(2*a);
    }
    x2 = c/(a*x1); // wzor viete'a
    return make_pair(x1, x2);
}

int main() {
    pair<float, float> szkolny, moj;
    // for (float i = 10; i <= pow(10, 15); i += 10000) {
    //     szkolny = pierw_szkolna(1.0, i, 1.0);
    //     moj = pierw(1.0, i, 1.0);
    //     printf("szkolna: %.30f %.30f\n", szkolny.first, szkolny.second);
    //     printf("vietowa: %.30f %.30f\n", moj.first, moj.second);
    // }
    for (float i = -10; i >= -pow(10, 15); i -= 10000) {
        szkolny = pierw_szkolna(1.0, i, 1.0);
        moj = pierw(1.0, i, 1.0);
        printf("szkolna: %.30f %.30f\n", szkolny.first, szkolny.second);
        printf("vietowa: %.30f %.30f\n", moj.first, moj.second);
    }
    return 0;
}