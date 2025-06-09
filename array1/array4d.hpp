#ifndef ARRAY4D_HPP
#define ARRAY4D_HPP

#include "array_base.hpp"

namespace array
{
    template <typename T>
    class Array4D : public ArrayBase<T> {
    public:
        Array4D() : ArrayBase<T>({0, 0, 0, 0}) { }

        explicit Array4D(const types::Size n1, const types::Size n2, const types::Size n3, const types::Size n4)
        : ArrayBase<T>({n1, n2, n3, n4}) { }

        inline types::Size Dim1() const { return this->shape_[0]; }
        inline types::Size Dim2() const { return this->shape_[1]; }
        inline types::Size Dim3() const { return this->shape_[2]; }
        inline types::Size Dim4() const { return this->shape_[3]; }

        inline T& operator()(const types::Index i, const types::Index j, const types::Index k, const types::Index l) {
            return this->ptr_raw_data_[((i * this->shape_[1] + j) * this->shape_[2] + k) * this->shape_[3] + l];
        }

        inline const T& operator()(const types::Index i, const types::Index j, const types::Index k, const types::Index l) const {
            return this->ptr_raw_data_[((i * this->shape_[1] + j) * this->shape_[2] + k) * this->shape_[3] + l];
        }

        T& At(const types::Index i, const types::Index j, const types::Index k, const types::Index l) {
        #ifdef ENABLE_DEBUG
            if (i >= Dim1() || j >= Dim2() || k >= Dim3() || l >= Dim4()) {
                throw std::out_of_range("Array4D index out of range");
            }
        #endif
            return (*this)(i, j, k, l);
        }

        const T& At(const types::Index i, const types::Index j, const types::Index k, const types::Index l) const {
        #ifdef ENABLE_DEBUG
            if (i >= Dim1() || j >= Dim2() || k >= Dim3() || l >= Dim4()) {
                throw std::out_of_range("Array4D index out of range");
            }
        #endif
            return (*this)(i, j, k, l);
        }

        virtual types::Size  NumDimensions() const override {
            return 4;
        };

        void Resize(const types::Size n1, const types::Size n2, const types::Size n3, const types::Size n4) {
            std::vector<types::Size> shape_new = {n1, n2, n3, n4};
            if (shape_new != this->shape_) {
                ArrayBase<T>::Resize(shape_new);
            }
        }

    private:
    };
}

#endif /* ARRAY4D_HPP */