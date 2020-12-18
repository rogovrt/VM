#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
#include <fstream>

std::pair <long double, long double> f(const std::pair <long double, long double>& u) {
    std::pair <long double, long double> f;
    f.first = u.second;
    f.second = 1000 * u.second - 1000 * pow(u.second, 3) - u.first;
    return f;
}

std::pair <long double, long double> mult(long double k, const std::pair <long double, long double>& u) {
    std::pair <long double, long double> u1;
    u1.first = k * u.first;
    u1.second = k * u.second;
    return u1;
}

std::pair <long double, long double> sum(const std::pair <long double, long double>& u, const std::pair <long double, long double>& u0) {
    std::pair <long double, long double> u1;
    u1.first = u.first + u0.first;
    u1.second = u.second + u0.second;
    return u1;
}

std::pair <long double, long double> sum4(const std::pair <long double, long double>& u0,
                                        const std::pair <long double, long double>& u1,
                                          const std::pair <long double, long double>& u2,
                                          const std::pair <long double, long double>& u3) {
    std::pair <long double, long double> u4;
    u4.first = u0.first + u1.first + u2.first + u3.first;
    u4.second = u0.second + u1.second + u2.second + u3.second;
    return u4;
}

int main() {
    std::pair <long double, long double> u0(0, 0.001);
    std::pair <long double, long double> u1;
    std::pair <long double, long double> f1;
    std::pair <long double, long double> f2;
    std::pair <long double, long double> f3;
    std::pair <long double, long double> f4;
    std::pair <long double, long double> u_;
    std::vector <long double> y;
    long double h = .0001;
    int j = 0;
    //std::ofstream fout("x.txt");
    //fout.setf(std::ios::fixed);
    //fout.precision(3);
    for (int i = 1; i < 1000/h + 1; ++i) {
        f1 = f(u0);
        f2 = f(sum(u0, mult(h/2, f1)));
        f3 = f(sum(u0, mult(h/2, f2)));
        f4 = f(sum(u0, mult(h, f3)));
        u_ = sum4(f1, mult(2, f2), mult(2, f3), f4);
        u1 = sum(u0, mult(h/6, u_));
        if ((i % 10000) == 0) {j++; std::cout << u1.first << "; " << j << std::endl;}
                                //fout << u1.first << ", ";}
        u0.first = u1.first;
        u0.second = u1.second;
    }
    return 0;
}