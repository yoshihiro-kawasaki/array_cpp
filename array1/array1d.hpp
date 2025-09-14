#ifndef ARRAY1D_HPP_
#define ARRAY1D_HPP_

#include "array_base.hpp"

namespace array
{
    template <typename T>
    class Array1D : public ArrayBase<T> {
    public:
        Array1D() : ArrayBase<T>({0}) { }

        explicit Array1D(const std::size_t n1) : ArrayBase<T>(std::initializer_list<std::size_t>{n1}) { }

        Array1D(const std::size_t n1, const T value)
        : ArrayBase<T>(std::initializer_list<std::size_t>{n1}, value) { }

        inline std::size_t Dim1() const { return this->shape_[0]; }

        inline T& operator()(const std::size_t i) {
            return this->ptr_raw_data_[i];
        }

        inline const T& operator()(const std::size_t i) const {
            return this->ptr_raw_data_[i];
        }

        T& At(const std::size_t i) {
        #ifdef ENABLE_DEBUG
            if (i >= Dim1()) {
                throw std::out_of_range("Array1D index out of range");
            }
        #endif
            return (*this)(i);
        }

        const T& At(const std::size_t i) const {
        #ifdef ENABLE_DEBUG
            if (i >= Dim1()) {
                throw std::out_of_range("Array1D index out of range");
            }
        #endif
            return (*this)(i);
        }

        void Resize(const std::size_t n1) {
            std::vector<std::size_t> shape_new = {n1};
            if (shape_new != this->shape_) {
                ArrayBase<T>::Resize(shape_new);
            }
        }

        virtual std::size_t  NumDimensions() const noexcept override {
            return 1;
        };

    private:
    };
}

#endif /* ARRAY1D_HPP_ */