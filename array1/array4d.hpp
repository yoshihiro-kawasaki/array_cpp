#ifndef ARRAY4D_HPP_
#define ARRAY4D_HPP_

#include "array_base.hpp"

namespace array
{
    template <typename T>
    class Array4D : public ArrayBase<T> {
    public:
        Array4D() : ArrayBase<T>({0, 0, 0, 0}) { }

        explicit Array4D(const std::size_t n1, const std::size_t n2, const std::size_t n3, const std::size_t n4)
        : ArrayBase<T>({n1, n2, n3, n4}) { }

        inline std::size_t Dim1() const { return this->shape_[0]; }
        inline std::size_t Dim2() const { return this->shape_[1]; }
        inline std::size_t Dim3() const { return this->shape_[2]; }
        inline std::size_t Dim4() const { return this->shape_[3]; }

        inline T& operator()(const std::size_t i, const std::size_t j, const std::size_t k, const std::size_t l) {
            return this->ptr_raw_data_[((i * this->shape_[1] + j) * this->shape_[2] + k) * this->shape_[3] + l];
        }

        inline const T& operator()(const std::size_t i, const std::size_t j, const std::size_t k, const std::size_t l) const {
            return this->ptr_raw_data_[((i * this->shape_[1] + j) * this->shape_[2] + k) * this->shape_[3] + l];
        }

        T& At(const std::size_t i, const std::size_t j, const std::size_t k, const std::size_t l) {
        #ifdef ENABLE_DEBUG
            if (i >= Dim1() || j >= Dim2() || k >= Dim3() || l >= Dim4()) {
                throw std::out_of_range("Array4D index out of range");
            }
        #endif
            return (*this)(i, j, k, l);
        }

        const T& At(const std::size_t i, const std::size_t j, const std::size_t k, const std::size_t l) const {
        #ifdef ENABLE_DEBUG
            if (i >= Dim1() || j >= Dim2() || k >= Dim3() || l >= Dim4()) {
                throw std::out_of_range("Array4D index out of range");
            }
        #endif
            return (*this)(i, j, k, l);
        }

        virtual std::size_t  NumDimensions() const noexcept override {
            return 4;
        };

        void Resize(const std::size_t n1, const std::size_t n2, const std::size_t n3, const std::size_t n4) {
            std::vector<std::size_t> shape_new = {n1, n2, n3, n4};
            if (shape_new != this->shape_) {
                ArrayBase<T>::Resize(shape_new);
            }
        }

    private:
    };
}

#endif /* ARRAY4D_HPP_ */