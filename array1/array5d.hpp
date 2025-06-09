#ifndef ARRAY5D_HPP
#define ARRAY5D_HPP

#include "array_base.hpp"

namespace array
{
    template <typename T>
    class Array5D : public ArrayBase<T> {
    public:
        Array5D() : ArrayBase<T>({0, 0, 0, 0, 0}) { }

        explicit Array5D(const types::Size n1, const types::Size n2, const types::Size n3, const types::Size n4, const types::Size n5)
        : ArrayBase<T>({n1, n2, n3, n4, n5}) { }

        inline types::Size Dim1() const { return this->shape_[0]; }
        inline types::Size Dim2() const { return this->shape_[1]; }
        inline types::Size Dim3() const { return this->shape_[2]; }
        inline types::Size Dim4() const { return this->shape_[3]; }
        inline types::Size Dim5() const { return this->shape_[4]; }

        inline T& operator()(const types::Index i, const types::Index j, const types::Index k, const types::Index l, const types::Index m) {
            return this->ptr_raw_data_[(((i * this->shape_[1] + j) * this->shape_[2] + k) * this->shape_[3] + l) * this->shape_[4] + m];
        }

        inline const T& operator()(const types::Index i, const types::Index j, const types::Index k, const types::Index l, const types::Index m) const {
            return this->ptr_raw_data_[(((i * this->shape_[1] + j) * this->shape_[2] + k) * this->shape_[3] + l) * this->shape_[4] + m];
        }

        T& At(const types::Index i, const types::Index j, const types::Index k, const types::Index l, const types::Index m) {
        #ifdef ENABLE_DEBUG
            if (i >= Dim1() || j >= Dim2() || k >= Dim3() || l >= Dim4() || m >= Dim5()) {
                throw std::out_of_range("Array5D index out of range");
            }
        #endif
            return (*this)(i, j, k, l, m);
        }

        const T& At(const types::Index i, const types::Index j, const types::Index k, const types::Index l, const types::Index m) const {
        #ifdef ENABLE_DEBUG
            if (i >= Dim1() || j >= Dim2() || k >= Dim3() || l >= Dim4() || m >= Dim5()) {
                throw std::out_of_range("Array5D index out of range");
            }
        #endif
            return (*this)(i, j, k, l, m);
        }

        virtual types::Size  NumDimensions() const override {
            return 5;
        };

        void Resize(const types::Size n1, const types::Size n2, const types::Size n3, const types::Size n4, const types::Size n5) {
            std::vector<types::Size> shape_new = {n1, n2, n3, n4, n5};
            if (shape_new != this->shape_) {
                ArrayBase<T>::Resize(shape_new);
            }
        }

    private:
    };
}

#endif /* ARRAY5D_HPP */