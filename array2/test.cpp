#include <iostream>
#include "array.hpp"

template <typename T>
array::Array<T> Test(const array::Array<T>& input) {
    array::Array<T> output(input.Shape());
    types::Size size = input.Size();
    const T* pin = input.Data();
    T* pout = output.Data();
    for (types::Index i = 0; i < size; ++i) {
        pout[i] = static_cast<T>(2) * pin[i];
    }
    return output;
}

int main()
{
    array::Array<double> a;
    a.Resize(10);
    a.One();

    array::Array<double> b = Test<double>(a);

    for (int i = 0; i < b.Size(); ++i) {
        std::cout << a(i) << " " << b(i) << std::endl;
    }

    return 0;
}