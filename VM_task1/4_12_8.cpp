#include <iostream>
#include <cmath>

int main() {
    long double eps  = pow(10., -3);

    long double a = .1;
    long double b = .5;
    long double x = a + (b - a) / 2;
    long double x1 = 1 / (2 * pow(2 * exp(1), .5) * exp(-pow(x, 2)));
    while(fabsl(x1 - x) > eps / 2) {
        x = x1;
        x1 = 1 / (2 * pow(2 * exp(1), .5) * exp(-pow(x, 2)));
    }

    a = 1.1;
    b = 1.5;
    long double z = a + (b - a) / 2;
    long double z1 = pow(log(2 * pow(2 * exp(1), .5) * z), .5);
    while(fabsl(z1 - z) > eps / 2) {
        z = z1;
        z1 = pow(log(2 * pow(2 * exp(1), .5) * z), .5);
    }

    std::cout << x << "; " << z << std::endl;
    std::cout << "answer : " << z - x << std::endl;

    return 0;
}