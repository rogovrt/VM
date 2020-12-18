#include <iostream>
#include <vector>
#include <cmath>
#include <utility>

void print_vector(const std::vector <long double>& x) {
    for (auto it = x.begin(); it < x.end(); ++it)
        std::cout << *it << " ; ";
    std::cout << std::endl;
}

std::pair <long double, long double> f(const std::pair <long double, long double>& u, long double x) {
    std::pair <long double, long double> f;
    f.first = u.second;
    f.second = sqrtl(-expl(u.second)*u.first + expl(1)*pow(u.first, 2)/logl(x) + pow(x, -2));
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

std::vector <long double> solve(long double y1) {
    std::pair <long double, long double> u0{expl(1), y1};
    std::pair <long double, long double> u1;
    std::pair <long double, long double> f1;
    std::pair <long double, long double> f2;
    std::pair <long double, long double> f3;
    std::pair <long double, long double> f4;
    std::pair <long double, long double> u_;
    std::vector <long double> y;
    long double h = .0001;
    long double x = expl(1);
    while (x < 7.3892) {
        f1 = f(u0, x);
        f2 = f(sum(u0, mult(h/2, f1)), x + h/2);
        f3 = f(sum(u0, mult(h/2, f2)), x + h/2);
        f4 = f(sum(u0, mult(h, f3)), x + h);
        u_ = sum4(f1, mult(2, f2), mult(2, f3), f4);
        u1 = sum(u0, mult(h/6, u_));
        x += h;
        long double eps = .00005;
        if (fabsl(x - expl(2)) < eps)
            y.push_back(u1.first);
        u0.first = u1.first;
        u0.second = u1.second;
    }
    return y;
}

std::vector <long double> solve_back(long double y1) {
    std::pair <long double, long double> u0{expl(1), y1};
    std::pair <long double, long double> u1;
    std::pair <long double, long double> f1;
    std::pair <long double, long double> f2;
    std::pair <long double, long double> f3;
    std::pair <long double, long double> f4;
    std::pair <long double, long double> u_;
    std::vector <long double> y;
    long double h = -.0001;
    long double x = expl(1);
    while (x > .49) {
        f1 = f(u0, x);
        f2 = f(sum(u0, mult(h/2, f1)), x + h/2);
        f3 = f(sum(u0, mult(h/2, f2)), x + h/2);
        f4 = f(sum(u0, mult(h, f3)), x + h);
        u_ = sum4(f1, mult(2, f2), mult(2, f3), f4);
        u1 = sum(u0, mult(h/6, u_));
        x += h;
        long double eps = .00005;
        if ((fabsl(x - 0.5) < eps) || (fabsl(x -1.) < eps)||
            (fabsl(x - 1.5) < eps) || (fabsl(x -2.) < eps)||
            (fabsl(x - 2.5) < eps)) {
            y.push_back(u1.first);
            std::cout << x << " ; " << u1.first << std::endl;
        }
        u0.first = u1.first;
        u0.second = u1.second;
    }
    return y;
}

long double F(long double z) {
    return solve(z).at(0) - 2*expl(2);
}

int main() {
    std::cout.setf(std::ios::fixed);
    std::cout.precision(6);
    long double z_mid = 1.5;
    long double z0 = 1.9;
    long double z1 = 2.;
    while(fabsl(F(z_mid)) > .0001) {
        z_mid = (z0 + z1) / 2;
        if ((F(z0)*F(z_mid)) < 0)
            z1 = z_mid;
        if ((F(z1)*F(z_mid)) < 0)
            z0 = z_mid;
    }
    print_vector(solve_back(z_mid));
    return 0;
}