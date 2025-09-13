#ifndef ARRAY2D_HPP_
#define ARRAY2D_HPP_

#include "array_base.hpp"
#include "array1d.hpp"

namespace array
{
    template <typename T>
    class Array2D : public ArrayBase<T> {
    public:
        Array2D() : ArrayBase<T>({0, 0}) { }

        explicit Array2D(const std::size_t n1, const std::size_t n2) : ArrayBase<T>({n1, n2}) { }

        inline std::size_t Dim1() const { return this->shape_[0]; }
        inline std::size_t Dim2() const { return this->shape_[1]; }

        inline T& operator()(const std::size_t i, const std::size_t j) {
            return this->ptr_raw_data_[i * this->shape_[1] + j];
        }

        inline const T& operator()(const std::size_t i, const std::size_t j) const {
            return this->ptr_raw_data_[i * this->shape_[1] + j];
        }

        T& At(const std::size_t i, const std::size_t j) {
        #ifdef ENABLE_DEBUG
            if (i >= Dim1() || j >= Dim2()) {
                throw std::out_of_range("Array2D index out of range");
            }
        #endif
            return (*this)(i, j);
        }

        const T& At(const std::size_t i, const std::size_t j) const {
        #ifdef ENABLE_DEBUG
            if (i >= Dim1() || j >= Dim2()) {
                throw std::out_of_range("Array2D index out of range");
            }
        #endif
            return (*this)(i, j);
        }

        virtual std::size_t  NumDimensions() const noexcept override {
            return 2;
        };

        void Resize(const std::size_t n1, const std::size_t n2) {
            std::vector<std::size_t> shape_new = {n1, n2};
            if (shape_new != this->shape_) {
                ArrayBase<T>::Resize(shape_new);
            }
        }

    private:
    };
}

#endif /* ARRAY2D_HPP_ */