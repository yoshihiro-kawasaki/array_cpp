#ifndef ARRAY3D_HPP
#define ARRAY3D_HPP

#include "array_base.hpp"

namespace array
{
    template <typename T>
    class Array3D : public ArrayBase<T> {
    public:
        Array3D() : ArrayBase<T>({0, 0, 0}) { }

        explicit Array3D(const types::Size n1, const types::Size n2, const types::Size n3)
        : ArrayBase<T>({n1, n2, n3}) { }

        inline types::Size Dim1() const { return this->shape_[0]; }
        inline types::Size Dim2() const { return this->shape_[1]; }
        inline types::Size Dim3() const { return this->shape_[2]; }

        inline T& operator()(const types::Index i, const types::Index j, const types::Index k) {
            return this->ptr_raw_data_[(i * this->shape_[1] + j) * this->shape_[2] + k];
        }

        inline const T& operator()(const types::Index i, const types::Index j, const types::Index k) const {
            return this->ptr_raw_data_[(i * this->shape_[1] + j) * this->shape_[2] + k];
        }

        T& At(const types::Index i, const types::Index j, const types::Index k) {
        #ifdef ENABLE_DEBUG
            if (i >= Dim1() || j >= Dim2() || k >= Dim3()) {
                throw std::out_of_range("Array3D index out of range");
            }
        #endif
            return (*this)(i, j, k);
        }

        const T& At(const types::Index i, const types::Index j, const types::Index k) const {
        #ifdef ENABLE_DEBUG
            if (i >= Dim1() || j >= Dim2() || k >= Dim3()) {
                throw std::out_of_range("Array3D index out of range");
            }
        #endif
            return (*this)(i, j, k);
        }

        virtual types::Size  NumDimensions() const override {
            return 3;
        };

        void Resize(const types::Size n1, const types::Size n2, const types::Size n3) {
            std::vector<types::Size> shape_new = {n1, n2, n3};
            if (shape_new != this->shape_) {
                ArrayBase<T>::Resize(shape_new);
            }
        }

    private:
    };
}

#endif /* ARRAY3D_HPP */