#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

long double f(long double x) {
    return 5*x*x*x - 2*x*x - 10*x - 1;
}

long double fprim(long double x) {
    return 15*x*x - 4*x - 10;
}

long double fprimprim(long double x) {
    return 30*x - 4;
}

int main()
{
    long double alfa = 1.6696215914155472779568933905380845317267812788486480712890625;
    long double x = 5;
    long double xp1, xm1;
    while (true) {
        long double temp = f(x)/fprim(x);
        long double tempx = xp1;
        xp1 = x - temp - (1/2 * fprimprim(x)/fprim(x)*temp*temp);
        if (x - xp1 < 0.0000000000000000000000000000000000001) break;
        xm1 = x;
        x = xp1;
        cout << setprecision(100);
        cout << x << endl; 
        cout << x << " " << xp1 << " " << xm1 << endl;
        long double p = log(x-alfa/xm1-alfa)/log(x-alfa/xm1-alfa);
        cout << "p: " << p << endl;
    }
	return 0;
}
