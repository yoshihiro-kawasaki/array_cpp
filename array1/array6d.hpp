#ifndef ARRAY6D_HPP_
#define ARRAY6D_HPP_

#include "array_base.hpp"

namespace array
{
    template <typename T>
    class Array6D : public ArrayBase<T> {
    public:
        Array6D() : ArrayBase<T>({0, 0, 0, 0, 0, 0}) { }

        explicit Array6D(const std::size_t n1, const std::size_t n2, const std::size_t n3, const std::size_t n4, const std::size_t n5, const std::size_t n6)
        : ArrayBase<T>({n1, n2, n3, n4, n5, n6}) { }

        inline std::size_t Dim1() const { return this->shape_[0]; }
        inline std::size_t Dim2() const { return this->shape_[1]; }
        inline std::size_t Dim3() const { return this->shape_[2]; }
        inline std::size_t Dim4() const { return this->shape_[3]; }
        inline std::size_t Dim5() const { return this->shape_[4]; }
        inline std::size_t Dim6() const { return this->shape_[5]; }

        inline T& operator()(const std::size_t i, const std::size_t j, const std::size_t k, const std::size_t l, const std::size_t m, const std::size_t n) {
            return this->ptr_raw_data_[((((i * this->shape_[1] + j) * this->shape_[2] + k) * this->shape_[3] + l) * this->shape_[4] + m) * this->shape_[5] + n];
        }

        inline const T& operator()(const std::size_t i, const std::size_t j, const std::size_t k, const std::size_t l, const std::size_t m, const std::size_t n) const {
            return this->ptr_raw_data_[((((i * this->shape_[1] + j) * this->shape_[2] + k) * this->shape_[3] + l) * this->shape_[4] + m) * this->shape_[5] + n];
        }

        T& At(const std::size_t i, const std::size_t j, const std::size_t k, const std::size_t l, const std::size_t m, const std::size_t n) {
        #ifdef ENABLE_DEBUG
            if (i >= Dim1() || j >= Dim2() || k >= Dim3() || l >= Dim4() || m >= Dim5() || n >= Dim6()) {
                throw std::out_of_range("Array6D index out of range");
            }
        #endif
            return (*this)(i, j, k, l, m, n);
        }

        const T& At(const std::size_t i, const std::size_t j, const std::size_t k, const std::size_t l, const std::size_t m, const std::size_t n) const {
        #ifdef ENABLE_DEBUG
            if (i >= Dim1() || j >= Dim2() || k >= Dim3() || l >= Dim4() || m >= Dim5() || n >= Dim6()) {
                throw std::out_of_range("Array5D index out of range");
            }
        #endif
            return (*this)(i, j, k, l, m, n);
        }

        virtual std::size_t  NumDimensions() const noexcept override {
            return 6;
        };

        void Resize(const std::size_t n1, const std::size_t n2, const std::size_t n3, const std::size_t n4, const std::size_t n5, const std::size_t n6) {
            std::vector<std::size_t> shape_new = {n1, n2, n3, n4, n5, n6};
            if (shape_new != this->shape_) {
                ArrayBase<T>::Resize(shape_new);
            }
        }

    private:
    };
}

#endif /* ARRAY6D_HPP_ */