#ifndef ARRAY1D_HPP
#define ARRAY1D_HPP

#include "array_base.hpp"

namespace array
{
    template <typename T>
    class Array1D : public ArrayBase<T> {
    public:
        Array1D() : ArrayBase<T>({0}) { }

        explicit Array1D(const types::Size n1) : ArrayBase<T>(std::initializer_list<types::Size>{n1}) { }

        inline types::Size Dim1() const { return this->shape_[0]; }

        inline T& operator()(const types::Index i) {
            return this->ptr_raw_data_[i];
        }

        inline const T& operator()(const types::Index i) const {
            return this->ptr_raw_data_[i];
        }

        T& At(const types::Size i) {
        #ifdef ENABLE_DEBUG
            if (i >= Dim1()) {
                throw std::out_of_range("Array1D index out of range");
            }
        #endif
            return (*this)(i);
        }

        const T& At(const types::Size i) const {
        #ifdef ENABLE_DEBUG
            if (i >= Dim1()) {
                throw std::out_of_range("Array1D index out of range");
            }
        #endif
            return (*this)(i);
        }

        void Resize(const types::Size n1) {
            std::vector<types::Size> shape_new = {n1};
            if (shape_new != this->shape_) {
                ArrayBase<T>::Resize(shape_new);
            }
        }

        virtual types::Size  NumDimensions() const override {
            return 1;
        };

    private:
    };
}

#endif /* ARRAY1D_HPP */