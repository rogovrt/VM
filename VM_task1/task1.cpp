#include <iostream>
#include <cmath>
#include <array>
#include <utility>

std::pair <double, double> solve(double x_st, double y_st, double eps) {
    std::array <double, 2> u1 = {x_st, y_st};
    std::array <double, 2> u = {x_st- eps * 10, y_st- eps * 10};
    std::array <double, 2> fu = {0, 0};
    std::array <double, 2> delta = {0, 0};
    while ((fabs(u[0] - u1[0]) > eps) and (fabs(u[1] - u1[0]) > eps)) {
        u[0] = u1[0];
        u[1] = u1[1];
        fu[0] = pow(u[0], 2) + pow(u[1], 2) - 1;
        fu[1] = tan(u[0]) - u[1];
        delta[0] = -fu[0] - 2 * u[1] * fu[1];
        delta[1] = -pow(cos(u[0]), -2) * fu[0] + 2 * u[0] * fu[1];
        double k = 1 / (2 * u[0] + 2 * u[1] * pow(cos(u[0]), -2));
        u1[0] = u[0] +  k * delta[0];
        u1[1] = u[1] +  k * delta[1];
    }
    return std::make_pair(u1[0], u1[1]);
}

int main() {
    std::cout.setf(std::ios::fixed);
    std::cout.precision(6);

    double x = 0.65; //on [0.6; 0.7]
    double y = 0.75; //on [0.7; 0.8]
    double eps = pow(10, -6);
    auto root1 = solve(x, y, eps);
    std::cout << root1.first << " ; " << root1.second << std::endl;

    x = -0.65; //on [-0.7; -0.6]
    y = -0.75; //on [-0.8; -0.7]
    auto root2 = solve(x, y, eps);
    std::cout << root2.first << " ; " << root2.second << std::endl;

    return 0;
}