#include <iostream>
#include <vector>
#include <cmath>

void print_vector(const std::vector <long double>& v) {
    for (int i =0 ; i < v.size(); ++i)
        std::cout << v[i] << " ; ";
    std::cout << std::endl;
}

long double diverse(long double fn, long double fk, long double h ){
    return (fn - fk) / h;
}

std::vector <long double> next_order(const std::vector <long double>& f, long double h) {
    std::vector <long double> f1;
    for (int i = 0; i < f.size() - 1; ++i)
        f1.push_back((f[i] - f[i + 1]) / h);
    return f1;
}

std::vector <long double> solve(const std::vector<long double>& m, const std::vector<long double>& u, const std::vector<long double> d, const std::vector<long double>& r) {
    int n = r.size();
    std::vector <long double> p(n - 1);
    std::vector <long double> q(n - 1);
    p[0] = - u[0] / m[0];
    q[0] = r[0] / m[0];
    for (int i = 1; i <= (n - 2); ++i) {
        p[i]  = - u[i] / (d[i] * p[i - 1] + m[i]);
        q[i] = r[i] / (d[i] * p[i - 1] + m[i]);
    }
    std::vector <long double> x(n);
    x[n - 1] = (r[n - 1] - q[n - 2] * d[n - 2]) / (m[n - 1] + p[n - 2] * d[n - 2]);
    for (int i = n - 2; i > -1; --i) {
        x[i] = p[i] * x[i + 1] + q[i];
    }
    return x;
}

int main() {

    std::vector <long double> t;
    for (long double i = 1910; i < 2010; i += 10)
        t.push_back(i);

    std::cout.setf(std::ios::fixed);
    std::cout.precision(8);
    std::vector <long double> f1 {92228496., 106021537., 123202624., 132164569., 151325798.,
                                 179323175., 203211926.,  226545805., 248709873., 281421906.};
    std::vector <long double> f = f1;
    std::vector <long double> fh;
    std::vector <long double> c;
    c.push_back(f1[0]);
    for (int i = 2; i < 11; ++i) {
        fh = next_order(f, -10 * (i - 1));
        c.push_back(fh[0]);
        f = fh;
    }
    long double res = 0;
    long double q = 1;
    for (int i = 0; i < c.size(); ++i) {
        if (i > 0)
            q *= 100 - (i - 1) * 10;
        res += c[i] * q;
    }
    std::cout << "newton population : " << res << std::endl;

    long double h = 10; //step
    double k = 0.5; // coef in tridiag matrix

    int n = f1.size();

    std::vector <long double> div(n - 2);
    for (int i = 0; i < (n - 2); ++i) {
        div[i] = 6 * diverse( diverse(f1[i + 2], f1[i + 1], h), diverse(f1[i + 1], f1[i], h), 2*h);
    }

    std::vector <long double> main(n - 2, 2.0);
    std::vector <long double> up(n - 3, k);
    std::vector <long double> down(n - 3, k);
    std::vector <long double> c1 = solve(main, up, down, div);
    c1.insert(c1.cend(), 0);
    int j = 9;
    long double t1 = 2010;
    long double a = f1[j];
    long double b = c1[j] * h / 3 + c1[j - 1] * h / 6 + diverse(f1[j], f1[j - 1], h);
    long double d = (c1[j] - c1[j - 1]) / h;
    long double res1 = a + b * (t1 - t[j]) + c1[j] / 2 * pow(t1 - t[j], 2) + d / 6 * pow(t1 - t[j], 3);
    std::cout << "splain population : " << res1 << std::endl;

    return 0;
}