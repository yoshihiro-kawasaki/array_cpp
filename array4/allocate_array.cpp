#include "allocate_array.hpp"
#include "array.hpp"

#include <iostream>
#include <chrono>

typedef double test_type;

/* test 1D */

void testAllocate1DArray()
{
    int n = 100000000;
    int *a;
    a = Allocate1dArray<int>(n);

    for (int i = 0; i < n; ++i) {
        a[i] = i;
        // std::cout << (&a[i]) << std::endl;
    }

    Delete1dArray<int>(a);

    return;
}

void testArray1D()
{
    int n = 100000000;
    Array1D<int> a(n);

    for (int i = 0; i < n; ++i) {
        a(i) = i;
        // std::cout << (&a(i)) << std::endl;
    }

    return;
}

/* test 2D */

void testAllocate2DArray()
{
    int n = 30000;
    int m = 20000;

    test_type **a;
    a = Allocate2dArray<test_type>(n, m);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            a[i][j] = i + j;
            // std::cout << (&a[i][j]) << " " << a[i][j] << std::endl;
        }
    }

    Delete2dArray<test_type>(a);
}


void testArray2D()
{
    int n = 30000;
    int m = 20000;

    Array2D<test_type> a(n, m);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            a(i, j) = i + j;
            // std::cout << (&a(i, j)) << " " << a(i, j) << std::endl;
        }
    }
}

/* test 3D */

void testAllocate3DArray()
{
    int n = 1000;
    int m = 1000;
    int l = 1000;

    test_type ***a;
    a = Allocate3dArray<test_type>(n, m, l);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < l; ++k) {
                a[i][j][k] = i + j + k;
                // std::cout << (&a[i][j][k]) << " " << a[i][j][k] << std::endl;
            }
        }
        // std::cout << std::endl;
    }

    Delete3dArray<test_type>(a);
}

void testArray3D()
{
    int n = 1000;
    int m = 1000;
    int l = 1000;

    Array3D<test_type> a(n, m, l);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < l; ++k) {
                a(i, j, k) = i + j + k;
                // std::cout << (&a(i, j, k)) << " " << a(i, j, k) << std::endl;
            }
        }
        // std::cout << std::endl;
    }
}



int main()
{
    std::chrono::system_clock::time_point start, end;
    start = std::chrono::system_clock::now();

    // testAllocate1DArray();
    // testArray1D();

    // testAllocate2DArray();
    testArray2D();

    // testAllocate3DArray();
    // testArray3D();

    end = std::chrono::system_clock::now();
    const double timed = static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
    std::cout << "time = " << (timed * 1.0e-3) << "sec" << std::endl;

    return 0;
}