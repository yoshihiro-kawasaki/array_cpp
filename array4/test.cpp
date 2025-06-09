#include "allocate_array.hpp"
#include <iostream>
#include <chrono>

void test()
{
    std::chrono::system_clock::time_point start, end;
    start = std::chrono::system_clock::now();

    /* ############################################# */

    const int n = 50000;

    array::Double2D a = array::Allocate2dArray<double>(n, n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i][j] = i + j;
        }
    }

    array::Delete2dArray<double>(a);

    /* ############################################# */

    end = std::chrono::system_clock::now();
    const double timed = static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
    std::cout << "time = " << (timed * 1.0e-3) << "sec" << std::endl;

    return;
}

int main()
{
    // int n = 2, m = 3, s = 4, t = 5;

    // int n = 3, m = 3, s = 3, t = 3;

    // int ****a;
    // a = array::Allocate4dArray<int>(n, m, s, t);

    // for (int i = 0; i < n; ++i) {
    //     for (int j = 0; j < m; ++j) {
    //         for (int k = 0; k < s; ++k) {
    //             for (int l = 0; l < t; ++l) {
    //                 std::cout << "(" << i << ", " << j << ", " << k << ", " << l << ") = " << (&a[i][j][k][l]) << std::endl;
    //             }
    //             std::cout << " " << std::endl;
    //         }
    //     }
    // }

    // array::Delete4dArray<int>(a);

    test();

    return 0;
}