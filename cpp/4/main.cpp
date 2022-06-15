#include <iostream>
#include "wielomian.hpp"

using namespace std;

int main()
{
    wielomian a;
    wielomian b(3);
    double wsp[4] = { 3, 1, 2, 4 };
    wielomian c(3, wsp);
    wielomian d({1, 2, 3, 4, 5});
    cout << a;
    cout << b;
    cout << c;
    cout << d;
    wielomian e = c;
    cout << e;
    cout << c;
    wielomian f(7);
    f = std::move(d);
    cout << f;
    cout << d;
    ////////////
    wielomian g;
    cin >> g;
    cout << g;

    cout << a + b;
    cout << a - b;
    cout << b * c;
    cout << c * 2.1;

    a += b;
    cout << a - a;
    b-=c;
    cout << b;
    b*=c;
    cout << b;
    a *= 5.2;
    cout << a;

    //c - 4x^3 + 2x^2 + x + 3
    cout << c(2) << endl;
    cout << c[3];
    return 0;
}