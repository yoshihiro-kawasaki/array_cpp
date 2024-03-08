#include "array.hpp"

#include <iostream>
#include <chrono>

int main()
{
    std::chrono::system_clock::time_point start, end;
    start = std::chrono::system_clock::now();

    /* ############################################# */

    const int n = 20000;

    Array2D<double> a(n, n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            a(i, j) = i + j;
        }
    }

    /* ############################################# */

    end = std::chrono::system_clock::now();
    const double timed = static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
    std::cout << "time = " << (timed * 1.0e-3) << "sec" << std::endl;

    return 0;
}