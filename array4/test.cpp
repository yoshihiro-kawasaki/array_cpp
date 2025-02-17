#include "array.hpp"

#include <iostream>
#include <chrono>


void test1()
{
    std::chrono::system_clock::time_point start, end;
    start = std::chrono::system_clock::now();

    /* ############################################# */

    const int n = 10000;

    array::Array2D<double> a(n, n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i][j] = i + j;
        }
    }

    /* ############################################# */

    end = std::chrono::system_clock::now();
    const double timed = static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
    std::cout << "time = " << (timed * 1.0e-3) << "sec" << std::endl;

    return;
}

void test2()
{
    const int n = 4;
    const int m = 3;
    const int l = 3;

    array::Array3D<double> a(n, m, l);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < l; ++k) {
                std::cout << (&a[i][j][k]) << std::endl;
            }
        }
    }

}

void test3()
{
    const int n = 4;
    const int m = 3;
    const int l = 3;
    const int p = 2;
    const int q = 3;

    array::DoubleArray5D a(n, m, l, p, q);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < l; ++k) {
                for (int u = 0; u < p; ++u) {
                    for (int s = 0; s < q; ++s) {
                        std::cout << (&a[i][j][k][u][s]) << std::endl;
                    }
                }
            }
        }
    }

}

void test4()
{
    const int n = 5;

    array::DoubleArray5D a(n, n, n, n, n);
    array::DoubleArray5D_I b(n, n, n, n, n, 5.0);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                for (int l = 0; l < n; ++l) {
                    for (int m = 0; m < n; ++m) {
                        a[i][j][k][l][m] = b[i][j][k][l][m];
                        std::cout << a[i][j][k][l][m] << std::endl;
                    }
                }
            }
        }
    }
}

int main()
{

    // test1();

    // test2();

    test3();

    // test4();

    return 0;
}