#include <iostream>
#include <array>
#include <fstream>

int main() {
    std::ofstream fout("out.txt");
    fout.setf(std::ios::fixed);
    fout.precision(1);
    std::array <std::array<long double, 201>, 2001> grid;
    long double t = .005;
    long double h = .01;

    for (int i = 0; i < 201; ++i)
        grid[0][i] = 0.;
    for (int i = 0; i < 2001; ++i)
        grid[i][100] = 1.;

    for (int i = 1; i < 2001; ++i) {
        for (int j = 101; j < 201; ++j)
            grid[i][j] = (1 + 2 * (grid[i-1][j]-grid[i-1][j-1])/h)*t + grid[i-1][j];
    }
    for (int i = 1; i < 2001; ++i) {
        for (int j = 99; j > -1; --j)
            grid[i][j] = (1 + 2 * (grid[i-1][j+1]-grid[i-1][j])/h)*t + grid[i-1][j];
    }

    fout << "t = 0.1\n";
    for (int j = 0; j < 201; ++j) {
        if (j % 10 == 0)
            fout << grid[20][j] << " ; ";
    }
    fout << std::endl;
    fout << std::endl;

    fout << "t = 1\n";
    for (int j = 0; j < 201; ++j) {
        if (j % 10 == 0)
            fout << grid[200][j] << " ; ";
    }
    fout << std::endl;
    fout << std::endl;

    fout << "t = 10\n";
    for (int j = 0; j < 201; ++j) {
        if (j % 10 == 0)
            fout << grid[2000][j] << " ; ";
    }

    return 0;
}
