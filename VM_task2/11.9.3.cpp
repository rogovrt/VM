#include <iostream>
#include <vector>
#include <cmath>

void print_vector(const std::vector <long double>& x) {
    std::cout << "size = " << x.size() << std::endl;
    for (auto it = x.begin(); it < x.end(); ++it)
        std::cout << *it << " ; ";
    std::cout << std::endl;
}

std::vector <long double> solve(const std::vector <long double>& start, const std::vector <long double>& x) {
    std::vector <long double> u1 = start;
    std::vector <long double> u2(2);
    std::vector <long double> f1(2);
    std::vector <long double> f2(2);
    std::vector <long double> y;
    y.push_back(start.at(0));
    long double h = x.at(1) - x.at(0);
    for (int i = 0; i < x.size() - 1; ++i) {
        f1.at(0) = u1.at(1);
        f1.at(1) = x.at(i) * sqrt(u1.at(0));
        f2.at(0) = u1.at(1) + h * f1.at(0);
        f2.at(1) = x.at(i + 1) * sqrt(u1.at(0) + h * f1.at(0));
        u2.at(0) = u1.at(0) + h * (f1.at(0) + f2.at(0)) / 2;
        u2.at(1) = u1.at(1) + h * (f1.at(1) + f2.at(1)) / 2;
        y.push_back(u2.at(0));
        u1 = u2;
        //u2.clear();
        //f1.clear();
        //f2.clear();
    }
    return y;
}

std::vector <long double> grid_create(long double a, long double b, long double n) {
    std::vector <long double> x;
    long double h = (b - a) / n;
    long double c = a;
    for (int i = 0; i < (n + 1); ++i) {
        x.push_back(c);
        c += h;
    }
    return x;
}

long double F(long double z, const std::vector <long double>& x) {
    return (solve({0, z}, x).at(1000) - 2);
}

int main() {
    std::cout.setf(std::ios::fixed);
    std::cout.precision(6);
    std::vector <long double> x = grid_create(0, 1, 1000);
    long double z0 = .5;
    long double z1 = 2;
    long double z_mid = 2;
    while (fabsl(F(z_mid, x)) > .0001) {
        if ((F(z0, x)*F(z_mid, x)) < 0)
            z1 = z_mid;
        if ((F(z1, x)*F(z_mid, x)) < 0)
            z0 = z_mid;
        z_mid = (z0 + z1) / 2;
    }
    std::cout << z_mid << std::endl;
    std::cout << solve({0, z_mid}, x).at(1000) << std::endl;
    return 0;
}