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
    f.second = -(pow(x, 2) - 3)*u.second - (pow(x, 2) - 3)*coshl(x)*u.first + 2 - 6*x + 2*pow(x, 3)+ (pow(x, 2) - 3)*expl(x)*sinhl(x)*(1+coshl(x))+
            coshl(x)*(expl(x)+pow(x,2)-1+pow(x, 4)-3*pow(x,2));
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
    return u1;
}

std::vector <long double> solve(long double y1) {
    std::pair <long double, long double> u0(0, y1);
    std::pair <long double, long double> u1;
    std::pair <long double, long double> f1;
    std::pair <long double, long double> f2;
    std::pair <long double, long double> f3;
    std::pair <long double, long double> f4;
    std::pair <long double, long double> u_;
    std::vector <long double> y;
    long double h = .00001;
    long double x = 0;
    while (x < 3.1416) {
        f1 = f(u0, x);
        f2 = f(sum(u0, mult(h/2, f1)), x);
        f3 = f(sum(u0, mult(h/2, f2)), x);
        f4 = f(sum(u0, mult(h, f3)), x);
        u_ = sum4(f1, mult(2, f2), mult(2, f3), f4);
        u1 = sum(u0, mult(h/6, u_));
        //if ((i % 10000) == 0) {j++; std::cout << u1.first << "; " << j << std::endl;}
        x += h;
        long double eps = .000001;
        if ((fabsl(x - 0.5) < .000001) || (fabsl(x -1.) < eps)||
            (fabsl(x - 1.5) < .000001) || (fabsl(x -2.) < eps)||
            (fabsl(x - 2.5) < .000001) || (fabsl(x -3.) < eps)|| (fabsl(x - 3.14159) < eps))
            y.push_back(u1.first);
        u0.first = u1.first;
        u0.second = u1.second;
    }
    return y;
}

long double F(long double z) {
    return solve(z).at(6) - pow(M_PI, 2);
}

int main() {
    std::cout.setf(std::ios::fixed);
    std::cout.precision(6);
    print_vector(solve(-93.));
    print_vector(solve(-92.));
    long double z_mid = 0.;
    long double z0 = -93.;
    long double z1 = -92.;
    while(fabsl(F(z_mid)) > .0001) {
        z_mid = (z0 + z1) / 2;
        if ((F(z0)*F(z_mid)) < 0)
            z1 = z_mid;
        if ((F(z1)*F(z_mid)) < 0)
            z0 = z_mid;
    }
    print_vector(solve(z_mid));
    return 0;
}