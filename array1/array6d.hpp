#ifndef ARRAY6D_HPP
#define ARRAY6D_HPP

#include "array_base.hpp"

namespace array
{
    template <typename T>
    class Array6D : public ArrayBase<T> {
    public:
        Array6D() : ArrayBase<T>({0, 0, 0, 0, 0, 0}) { }

        explicit Array6D(const types::Size n1, const types::Size n2, const types::Size n3, const types::Size n4, const types::Size n5, const types::Size n6)
        : ArrayBase<T>({n1, n2, n3, n4, n5, n6}) { }

        inline types::Size Dim1() const { return this->shape_[0]; }
        inline types::Size Dim2() const { return this->shape_[1]; }
        inline types::Size Dim3() const { return this->shape_[2]; }
        inline types::Size Dim4() const { return this->shape_[3]; }
        inline types::Size Dim5() const { return this->shape_[4]; }
        inline types::Size Dim6() const { return this->shape_[5]; }

        inline T& operator()(const types::Index i, const types::Index j, const types::Index k, const types::Index l, const types::Index m, const types::Index n) {
            return this->ptr_raw_data_[((((i * this->shape_[1] + j) * this->shape_[2] + k) * this->shape_[3] + l) * this->shape_[4] + m) * this->shape_[5] + n];
        }

        inline const T& operator()(const types::Index i, const types::Index j, const types::Index k, const types::Index l, const types::Index m, const types::Index n) const {
            return this->ptr_raw_data_[((((i * this->shape_[1] + j) * this->shape_[2] + k) * this->shape_[3] + l) * this->shape_[4] + m) * this->shape_[5] + n];
        }

        T& At(const types::Index i, const types::Index j, const types::Index k, const types::Index l, const types::Index m, const types::Index n) {
        #ifdef ENABLE_DEBUG
            if (i >= Dim1() || j >= Dim2() || k >= Dim3() || l >= Dim4() || m >= Dim5() || n >= Dim6()) {
                throw std::out_of_range("Array6D index out of range");
            }
        #endif
            return (*this)(i, j, k, l, m, n);
        }

        const T& At(const types::Index i, const types::Index j, const types::Index k, const types::Index l, const types::Index m, const types::Index n) const {
        #ifdef ENABLE_DEBUG
            if (i >= Dim1() || j >= Dim2() || k >= Dim3() || l >= Dim4() || m >= Dim5() || n >= Dim6()) {
                throw std::out_of_range("Array5D index out of range");
            }
        #endif
            return (*this)(i, j, k, l, m, n);
        }

        virtual types::Size  NumDimensions() const override {
            return 6;
        };

        void Resize(const types::Size n1, const types::Size n2, const types::Size n3, const types::Size n4, const types::Size n5, const types::Size n6) {
            std::vector<types::Size> shape_new = {n1, n2, n3, n4, n5, n6};
            if (shape_new != this->shape_) {
                ArrayBase<T>::Resize(shape_new);
            }
        }

    private:
    };
}

#endif /* ARRAY6D_HPP */