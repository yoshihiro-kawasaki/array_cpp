#ifndef ARRAY2D_HPP
#define ARRAY2D_HPP

#include "array_base.hpp"
#include "array1d.hpp"

namespace array
{
    template <typename T>
    class Array2D : public ArrayBase<T> {
    public:
        Array2D() : ArrayBase<T>({0, 0}) { }

        explicit Array2D(const types::Size n1, const types::Size n2) : ArrayBase<T>({n1, n2}) { }

        inline types::Size Dim1() const { return this->shape_[0]; }
        inline types::Size Dim2() const { return this->shape_[1]; }

        inline T& operator()(const types::Index i, const types::Index j) {
            return this->ptr_raw_data_[i * this->shape_[1] + j];
        }

        inline const T& operator()(const types::Index i, const types::Index j) const {
            return this->ptr_raw_data_[i * this->shape_[1] + j];
        }

        T& At(const types::Size i, const types::Size j) {
        #ifdef ENABLE_DEBUG
            if (i >= Dim1() || j >= Dim2()) {
                throw std::out_of_range("Array2D index out of range");
            }
        #endif
            return (*this)(i, j);
        }

        const T& At(const types::Size i, const types::Size j) const {
        #ifdef ENABLE_DEBUG
            if (i >= Dim1() || j >= Dim2()) {
                throw std::out_of_range("Array2D index out of range");
            }
        #endif
            return (*this)(i, j);
        }

        virtual types::Size  NumDimensions() const override {
            return 2;
        };

        void Resize(const types::Size n1, const types::Size n2) {
            std::vector<types::Size> shape_new = {n1, n2};
            if (shape_new != this->shape_) {
                ArrayBase<T>::Resize(shape_new);
            }
        }

    private:
    };
}

#endif /* ARRAY2D_HPP */