#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
#include <fstream>
#include <algorithm>

const long double mu = 6.67 * 5.99 * pow(10, 13);

std::pair <long double, long double> f(const std::pair <long double, long double>& u, const long double r) {
    std::pair <long double, long double> f;
    f.first = u.second;
    f.second = -mu * u.first / pow(r, 3);
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

long double rad(long double x, long double y) {
    return sqrt(pow(x, 2) + pow(y, 2));
}

long double vel(long double vx, long double vy) {
    return sqrt(pow(vx, 2) + pow(vy, 2));
}

void solve_double(long double v) {
    //std::ofstream fout("kepler.txt");
    //fout.setf(std::ios::fixed);
    //fout.precision(3);
    std::pair <long double, long double> u0x{pow(10, 7), 0};
    std::pair <long double, long double> u1x;
    std::pair <long double, long double> u0y{0, 7.91 * 1000 - v};
    std::pair <long double, long double> u1y;
    std::pair <long double, long double> f1;
    std::pair <long double, long double> f2;
    std::pair <long double, long double> f3;
    std::pair <long double, long double> f4;
    std::pair <long double, long double> u_;
    long double h = 1;
    long double r = rad(u0x.first, u0y.first);
    int i = 0;
    std::cout << "V = " << v << std::endl;
    while(r > 6380*1000) {
    //while(i < 40000) {
        //fout << u0x.first << ", ";
        f1 = f(u0x, r);
        f2 = f(sum(u0x, mult(h/2, f1)), r);
        f3 = f(sum(u0x, mult(h/2, f2)), r);
        f4 = f(sum(u0x, mult(h, f3)), r);
        u_ = sum4(f1, mult(2, f2), mult(2, f3), f4);
        u1x = sum(u0x, mult(h/6, u_));
        u0x.first = u1x.first;
        u0x.second = u1x.second;
        f1 = f(u0y, r);
        f2 = f(sum(u0y, mult(h/2, f1)), r);
        f3 = f(sum(u0y, mult(h/2, f2)), r);
        f4 = f(sum(u0y, mult(h, f3)), r);
        u_ = sum4(f1, mult(2, f2), mult(2, f3), f4);
        u1y = sum(u0y, mult(h/6, u_));
        u0y.first = u1y.first;
        u0y.second = u1y.second;
        r = rad(u0x.first, u0y.first);
        v = vel(u0x.second, u0y.second);
        //fout << v/pow(r, 2.5)*pow(10,13) << ", ";
        ++i;
    }
    std::cout << i << std::endl;
}

std::vector <long double> eps(long double v, long double h) {
    //std::ofstream fout("kepler.txt");
    //fout.setf(std::ios::fixed);
    //fout.precision(3);
    std::pair <long double, long double> u0x{pow(10, 7), 0};
    std::pair <long double, long double> u1x;
    std::pair <long double, long double> u0y{0, 7.91 * 1000 - v};
    std::pair <long double, long double> u1y;
    std::pair <long double, long double> f1;
    std::pair <long double, long double> f2;
    std::pair <long double, long double> f3;
    std::pair <long double, long double> f4;
    std::pair <long double, long double> u_;
    long double r = rad(u0x.first, u0y.first);
    int i = 0;
    int h_obr = 1/h;
    //std::cout << "V = " << v << std::endl;
    std::vector <long double> sol;
    while(r > 6380*1000) {
        //while(i < 40000) {
        //fout << u0x.first << ", ";
        f1 = f(u0x, r);
        f2 = f(sum(u0x, mult(h/2, f1)), r);
        f3 = f(sum(u0x, mult(h/2, f2)), r);
        f4 = f(sum(u0x, mult(h, f3)), r);
        u_ = sum4(f1, mult(2, f2), mult(2, f3), f4);
        u1x = sum(u0x, mult(h/6, u_));
        u0x.first = u1x.first;
        u0x.second = u1x.second;
        f1 = f(u0y, r);
        f2 = f(sum(u0y, mult(h/2, f1)), r);
        f3 = f(sum(u0y, mult(h/2, f2)), r);
        f4 = f(sum(u0y, mult(h, f3)), r);
        u_ = sum4(f1, mult(2, f2), mult(2, f3), f4);
        u1y = sum(u0y, mult(h/6, u_));
        u0y.first = u1y.first;
        u0y.second = u1y.second;
        r = rad(u0x.first, u0y.first);
        if ((i % (h_obr*100)) == 0)
            sol.push_back(r);
        //fout << v/pow(r, 2.5)*pow(10,13) << ", ";
        ++i;
    }
    //std::cout << i << std::endl;
    return sol;
}

int main() {
    std::cout.setf(std::ios::fixed);
    std::cout.precision(6);
    solve_double(2.332*1000); //first in
    //solve_double(2.32*1000); out
    //solve_double(1.*1000);
    //----------------------------------//
    std::vector <long double> y1 = eps(2.332*1000, 1);
    std::vector <long double> y2 = eps(2.332*1000, .5);
    std::vector <long double> y4 = eps(2.332*1000, .25);
    std::vector <long double> y8 = eps(2.332*1000, .125);
    std::cout << y1.size() << "; " << y2.size() << "; " << y4.size() << "; " << y8.size() << std::endl;
    std::vector <long double> div(37);

    for (int i = 0; i < 37; ++i)
        div.push_back(fabsl(y1[i]-y2[i]));
    long double max_div = *std::max_element(div.begin(), div.end());
    std::cout << max_div / (pow(2, 4) - 1) << std::endl;
    div.clear();

    for (int i = 0; i < 37; ++i)
        div.push_back(fabsl(y2[i]-y4[i]));
    max_div = *std::max_element(div.begin(), div.end());
    std::cout << max_div / (pow(2, 4) - 1) << std::endl;
    div.clear();

    for (int i = 0; i < 37; ++i)
        div.push_back(fabsl(y4[i]-y8[i]));
    max_div = *std::max_element(div.begin(), div.end());
    std::cout << max_div / (pow(2, 4) - 1) << std::endl;

    return 0;
}