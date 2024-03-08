#include "array.hpp"

#include <iostream>
#include <chrono>


void test()
{
    std::chrono::system_clock::time_point start, end;
    start = std::chrono::system_clock::now();

    /* ############################################# */

    const int n = 50000;

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
    int n = 4;
    int m = 3;
    int l = 3;

    // NRvector<double> a(n, 1.0);

    // for (int i = 0; i < n; ++i) {
    //     std::cout << a[i] << std::endl;
    // }

    // Array2D<double> b(n, m);

    // for (int i = 0; i < n; ++i) {
    //     for (int j = 0; j < m; ++j) {
    //         b[i][j] = i + j;
    //         std::cout << (&b[i][j]) << std::endl;
    //     }
    //     std::cout << std::endl;
    // }

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
    int n = 4;
    int m = 3;
    int l = 3;
    int p = 2;
    int q = 3;

    // NRvector<double> a(n, 1.0);

    // for (int i = 0; i < n; ++i) {
    //     std::cout << a[i] << std::endl;
    // }

    // Array2D<double> b(n, m);

    // for (int i = 0; i < n; ++i) {
    //     for (int j = 0; j < m; ++j) {
    //         b[i][j] = i + j;
    //         std::cout << (&b[i][j]) << std::endl;
    //     }
    //     std::cout << std::endl;
    // }

    // array::Array4D<double> a(n, m, l, p);

    // for (int i = 0; i < n; ++i) {
    //     for (int j = 0; j < m; ++j) {
    //         for (int k = 0; k < l; ++k) {
    //             for (int l = 0; l < p; ++l) {
    //                 std::cout << (&a[i][j][k][l]) << std::endl;
    //             }
    //         }
    //     }
    // }

    array::DoubleArray5D a(n, m, l, p, q);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < l; ++k) {
                for (int l = 0; l < p; ++l) {
                    for (int m = 0; m < q; ++m) {
                        std::cout << (&a[i][j][k][l]) << std::endl;
                    }
                }
            }
        }
    }

}

void test4()
{
    // int n = 5;
    // array::DoubleArray1D a(n);

    // a = 5.0;

    // for (int i = 0; i < n; ++i) {
    //     std::cout << a[i] << std::endl;
    // }

    int n = 5;
    int m = 4;

    array::DoubleArray2D a(n, m);

    a = 4.0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cout << a[i][j] << std::endl;
        }
    }
}

void test5()
{
    int n = 5;
    // array::DoubleArray3D a(n, n, n);
    // array::DoubleArray3D_I b(n, n, n);

    // for (int i = 0; i < n; ++i) {
    //     for (int j = 0; j < n; ++j) {
    //         for (int k = 0; k < n; ++k) {
    //             a[i][j][k] = b[i][j][k];
    //         }
    //     }
    // }

    // array::DoubleArray4D a(n, n, n, n);
    // array::DoubleArray4D_I b(n, n, n, n, 3.0);

    // for (int i = 0; i < n; ++i) {
    //     for (int j = 0; j < n; ++j) {
    //         for (int k = 0; k < n; ++k) {
    //             for (int l = 0; l < n; ++l) {
    //                 a[i][j][k][l] = b[i][j][k][l];
    //                 std::cout << a[i][j][k][l] << std::endl;
    //             }
    //         }
    //     }
    // }


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

    // test();

    // test2();

    // test4();

    test5();

    return 0;
}