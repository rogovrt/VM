//solve integral  sin(100*x)*exp(-x^2)*cos(2*x)*dx from 0 to 3 result

#include <iostream>
#include <cmath>

long double f(long double x) {
    return sin(100 * x) * exp(-pow(x, 2)) * cos(2 * x);
}

int main() {
    std::cout.setf(std::ios::fixed);
    std::cout.precision(8);
    long double h = .001;
    long double x = 0;
    int n = 3. / h;
    long double res = 0;
    for (int i = 0; i < n; ++i) {
        res += .125 * (f(x) + 3*f(x + h/3) +  3*f(x + 2*h/3) + f(x + h)) * h;
        x += h;
    }
    std::cout << "Integral = " << res << std::endl;
    //h = .001 -> 0.01000622
    //h = .0001 -> 0.01000611
    //h = .00001 -> 0.01000610
    //wolfram -> 0.1000609786
    return 0;
}