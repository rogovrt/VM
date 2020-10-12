#include <iostream>
#include <vector>

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

int main() {
    /*
    std::vector <long double> t;
    for (long double i = 1910; i < 2010; i += 10)
        t.push_back(i)
    */
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
        print_vector(fh);
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

    return 0;
}