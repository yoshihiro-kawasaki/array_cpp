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
    // array::Array1D<double> a(N, 1.0), b(N, 2.0), c(N);
    // add1(a, b, c);
    // for (int i = 0; i < 10; ++i) {
    //     std::cout << a(i) << " " << b(i) << " " << c(i) << std::endl;
    // }

    // std::cout << "Array2D" << std::endl;
    // const int N = 100;
    // array::Array2D<double> a(N, N, 1.0), b(N, N, 2.0), c(N, N);
    // add2(a, b, c);
    // array::Array1D<double> d = c.Flatten();
    // std::cout << d.Size() << std::endl;
    // for (int i = 0; i < 3; ++i) {
    //     for (int j = 0; j < 3; ++j) {
    //         std::cout << a(i, j) << " " << b(i, j) << " " << c(i, j) << std::endl;
    //     }
    // }

    // array::Array2D<int> a(3, 4);
    // std::cout << a.Dim1() << " " << a.Dim2() << " " << a.Data() << std::endl;

    // // a.Reshape(4, 3);
    // a.Resize(5, 6);
    // std::cout << a.Dim1() << " " << a.Dim2() << " " << a.Data() << std::endl;    

    // array::Array3D<int> b(3, 4, 5);
    // b.Reshape(3, 5, 4);
    // std::cout << b.Dim1() << " " << b.Dim2() << " " << b.Dim3() << std::endl;

    array::Array2D<double> b(3, 5);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 5; ++j) {
            b(i, j) = i * j + 1;
        }
    }
    array::Array2D<double> c;
    c.ResizeLike(b);
    c.Copy(b);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 5; ++j) {
            std::cout << b(i, j) << " " << c(i, j) << std::endl;
        }
    }

    return 0;
}