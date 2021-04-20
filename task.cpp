#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Core>
#include <vector>
#include <iomanip>

using namespace Eigen;

void solve(int n, int m) { // по возможности квадратная
	double h_n = 1. / (n - 1);
	double h_m = 1. / (m - 1);
	int s = (m-2) + (n-2)*(m-1);
	MatrixXd A(s, s);
	for (int i = 0; i < s; ++i) {
                for (int j = 0; j < s; ++j)
                        A(i, j) = 0.;
        }
	double r = 0.;
	for (int i = 0; i < s; ++i) {
		A(i, i) = - 2./pow(h_n, 2) - 2./pow(h_m, 2);
		if (i > 0)
			A(i, i-1) = 1./pow(h_m, 2);
		if (i < s-1)
			A(i, i+1) = 1./pow(h_m, 2);
		if (i < s-m+1) {
			r = 1 + ((i+m-1)/(m-1) + 1)*h_n;
			A(i, i+m-1) = 1./pow(h_n, 2) - 1/(2*h_n*r);
		}
		if (i > m-2) {
			r = 1 + ((i-m+1)/(m-1) + 1)*h_n;
			A(i, i-m+1) = 1./pow(h_n, 2) - 1/(2*h_n*r);
		}
	}
	VectorXd u(s);
	VectorXd f(s);
	for (int i = 0; i < s; ++i) {
		u(i) = .001;
		f(i) = 0.;
	}
	u = A.colPivHouseholderQr().solve(f);
	//for (int i = 0; i < 100; ++i) {
	//	u = (MatrixXd::Identity(s, s) -  A)*u;
	//}
	//u = (A.transpose() * A).ldlt().solve(A.transpose() * f);
	std::cout << u << std::endl;
}

int main() {
	/**
  MatrixXd m(2,2);
  m(0,0) = 3;
  m(1,0) = 2.5;
  m(0,1) = -1;
  m(1,1) = m(1,0) + m(0,1);
  std::cout << "Here is the matrix m:\n" << m << std::endl;
  VectorXd v(2);
  v(0) = 4;
  v(1) = v(0) - 1;
  std::cout << "Here is the vector v:\n" << v << std::endl;
	
	MatrixXf A = MatrixXf::Random(3, 2);
VectorXf b = VectorXf::Random(3);
std::cout << "The solution using the QR decomposition is:\n"
     << A.colPivHouseholderQr().solve(b) << std::endl;
	*/
	solve(41, 41);
}
