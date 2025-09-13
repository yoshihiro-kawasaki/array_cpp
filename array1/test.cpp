#include <iostream>

#include "array.hpp"

void add1(const array::Array1D<double> &a, const array::Array1D<double> &b, array::Array1D<double> &c) {
    int size = a.Size();
    for (std::size_t i = 0; i < size; ++i) {
        c(i) = a(i) + b(i);
    }
    return;
}


void add2(const array::Array2D<double> &a, const array::Array2D<double> &b, array::Array2D<double> &c) {
    std::size_t ndim1 = a.Dim1();
    std::size_t ndim2 = a.Dim2();
    for (std::size_t i = 0; i < ndim1; ++i) {
        for (std::size_t j = 0; j < ndim2; ++j) {
            c(i, j) = a(i, j) + b(i, j);
        }
    }
    return;
}


void add3(const array::Array3D<double> &a, const array::Array3D<double> &b, array::Array3D<double> &c) {
    std::size_t ndim1 = a.Dim1();
    std::size_t ndim2 = a.Dim2();
    std::size_t ndim3 = a.Dim3();
    for (std::size_t i = 0; i < ndim1; ++i) {
        for (std::size_t j = 0; j < ndim2; ++j) {
            for (std::size_t k = 0; j < ndim3; ++k) {
                c(i, j, k) = a(i, j, k) + b(i, j, k);
            }
        }
    }
    return;
}


int main() {
    // const int N = 1000;
    // array::Array1D<double> a(N), b(N), c(N);
    // a.Fill(1.0);
    // b.Fill(2.0);
    // add1(a, b, c);

    std::cout << "Array2D" << std::endl;
    const int N = 100;
    array::Array2D<double> a(N, N), b(N, N), c(N, N);
    a.Fill(1.0);
    b.Fill(2.0);
    add2(a, b, c);
    array::Array1D<double> d = c.Flatten();
    std::cout << d.Size() << std::endl;

    return 0;
}