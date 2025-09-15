#ifndef ARRAY5D_HPP_
#define ARRAY5D_HPP_

#include "array_base.hpp"

namespace array
{
    template <typename T>
    class Array5D : public ArrayBase<T> {
    public:
        Array5D() : ArrayBase<T>({0, 0, 0, 0, 0}) { }

        explicit Array5D(const std::size_t n1, const std::size_t n2, const std::size_t n3, const std::size_t n4, const std::size_t n5)
        : ArrayBase<T>({n1, n2, n3, n4, n5}) { }

        Array5D(const std::size_t n1, const std::size_t n2, const std::size_t n3, const std::size_t n4, const std::size_t n5, const T value)
        : ArrayBase<T>({n1, n2, n3, n4, n5}, value) { }

        inline std::size_t Dim1() const { return this->shape_[0]; }
        inline std::size_t Dim2() const { return this->shape_[1]; }
        inline std::size_t Dim3() const { return this->shape_[2]; }
        inline std::size_t Dim4() const { return this->shape_[3]; }
        inline std::size_t Dim5() const { return this->shape_[4]; }

        inline T& operator()(const std::size_t i, const std::size_t j, const std::size_t k, const std::size_t l, const std::size_t m) {
            return this->ptr_raw_data_[(((i * this->shape_[1] + j) * this->shape_[2] + k) * this->shape_[3] + l) * this->shape_[4] + m];
        }

        inline const T& operator()(const std::size_t i, const std::size_t j, const std::size_t k, const std::size_t l, const std::size_t m) const {
            return this->ptr_raw_data_[(((i * this->shape_[1] + j) * this->shape_[2] + k) * this->shape_[3] + l) * this->shape_[4] + m];
        }

        T& At(const std::size_t i, const std::size_t j, const std::size_t k, const std::size_t l, const std::size_t m) {
        #ifdef ENABLE_DEBUG
            if (i >= Dim1() || j >= Dim2() || k >= Dim3() || l >= Dim4() || m >= Dim5()) {
                throw std::out_of_range("Array5D index out of range");
            }
        #endif
            return (*this)(i, j, k, l, m);
        }

        const T& At(const std::size_t i, const std::size_t j, const std::size_t k, const std::size_t l, const std::size_t m) const {
        #ifdef ENABLE_DEBUG
            if (i >= Dim1() || j >= Dim2() || k >= Dim3() || l >= Dim4() || m >= Dim5()) {
                throw std::out_of_range("Array5D index out of range");
            }
        #endif
            return (*this)(i, j, k, l, m);
        }

        virtual std::size_t  NumDimensions() const noexcept override {
            return 5;
        };

        void Resize(const std::size_t n1, const std::size_t n2, const std::size_t n3, const std::size_t n4, const std::size_t n5) {
            std::vector<std::size_t> shape_new = {n1, n2, n3, n4, n5};
            if (shape_new != this->shape_) {
                ArrayBase<T>::Resize(shape_new);
            }
        }

        void Reshape(const std::size_t n1, const std::size_t n2, const std::size_t n3, const std::size_t n4, const std::size_t n5) {
            std::vector<std::size_t> shape_new = {n1, n2, n3, n4, n5};
            if (shape_new != this->shape_) {
                ArrayBase<T>::Reshape(shape_new);
            }
        }

    private:
    };
}

#endif /* ARRAY5D_HPP_ */