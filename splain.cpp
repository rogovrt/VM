#include <iostream>
#include <vector>
#include <cmath>

double diverse(double f1, double f2, double h ){
    return (f2 - f1) / h;
}

void read_vector(std::vector <double>& v, int n) {
    for (int i = 0; i < n; ++i) {
        std::cin >> v[i];
    }
};

void print_vector(const std::vector <double>& v) {
	for (int i =0 ; i < v.size(); ++i)
		std::cout << v[i] << std::endl;
}

std::vector <double> solve(const std::vector<double>& m, const std::vector<double>& u, const std::vector<double> d, const std::vector<double>& r) {
	int n = r.size();
	std::vector <double> p(n - 1);
	std::vector <double> q(n - 1);
	p[0] = - u[0] / m[0];
	q[0] = r[0] / m[0];
	for (int i = 1; i <= (n - 2); ++i) {
		p[i]  = - u[i] / (d[i] * p[i - 1] + m[i]);
		q[i] = r[i] / (d[i] * p[i - 1] + m[i]);
	}
	std::vector <double> x(n);
	x[n - 1] = (r[n - 1] - q[n - 2] * d[n - 2]) / (m[n - 1] + p[n - 2] * d[n - 2]);
	for (int i = n - 2; i > -1; --i) {
		x[i] = p[i] * x[i + 1] + q[i];
	}
	return x;
}

int main() {
    double h = 0.1; //step
    double k = 0.5; // coef in tridiag matrix

    std::vector <double> f{-0.1013, -0.0002, 0.1000, 0.2002, 0.3013, //initialization of points 
    			0.4045, 0.5106, 0.6206, 0.7354, 0.8558};
    int n = f.size();
    std::vector <double> x(10);
    for (int i = 0; i < n; ++i) 
	    x[i] = -0.2 + i * h;

    std::vector <double> div(n - 2);
    for (int i = 0; i < (n - 2); ++i) {
        div[i] = 6 * diverse( diverse(f[i + 2], f[i + 1], h), diverse(f[i + 1], f[i], h), 2*h);
    }
	
    std::vector <double> main(n - 2, 2.0);
    std::vector <double> up(n - 3, k);
    std::vector <double> down(n - 3, k);
    std::vector <double> c = solve(main, up, down, div);
    c.insert(c.cend(), 0);

    double t = 0.25;
    int j = (t + 0.2) / h - 0.5;
    double a = f[j];
    double b = c[j] * h / 3 + c[j - 1] * h / 6 + diverse(f[j], f[j - 1], h);
    double d = (c[j] - c[j - 1]) / h;
    double res = a + b * (t - x[j]) + c[j] / 2 * pow(t - x[j], 2) + d / 6 * pow(t - x[j], 3);

    std::cout << res << std::endl;
}
