#ifndef ARRAY_BASE_HPP
#define ARRAY_BASE_HPP

#include <vector>
#include <algorithm>
#include <initializer_list>
#include <limits>
#include <cmath>

#include "types.hpp"
#include "array1d.hpp"

// template <typename T>
// class Array1D;

namespace array
{
    template <typename T>
    class Array1D;

    enum class ArrayStatus {
        Empty,
        Allocated
    };

    template <typename T>
    class ArrayBase {
    public:
        using value_type = T;

        ArrayBase() : shape_({}), size_(0), ptr_raw_data_(nullptr), status_(ArrayStatus::Empty) { }

        ArrayBase(std::initializer_list<types::Size> shape)
        : shape_(shape), size_(ComputeSize(shape_)), ptr_raw_data_(nullptr), status_(ArrayStatus::Empty) {
            AllocateArray();
        }

        // copy constructor
        ArrayBase(const ArrayBase& other)
        : shape_(other.shape_), size_(other.size_), ptr_raw_data_(nullptr), status_(ArrayStatus::Empty) {
            AllocateArray();
            if (other.IsAllocated()) {
                std::copy(other.Begin(), other.End(), ptr_raw_data_);
            }
        }

        // copy operator=
        ArrayBase& operator=(const ArrayBase& other) {
            if (this == &other) {
                return *this;
            }

            if (shape_ != other.shape_) {
                DeleteArray();
                shape_ = other.shape_;
                size_ = other.size_;
                AllocateArray();
            }

            if (other.IsAllocated()) {
                std::copy(other.Begin(), other.End(), ptr_raw_data_);
            }
            return *this;
        }

        // move constructor
        ArrayBase(ArrayBase&& other) noexcept
        : shape_(std::move(other.shape_)), size_(other.size_), ptr_raw_data_(other.ptr_raw_data_), status_(other.status_) {
            other.size_ = 0;
            other.ptr_raw_data_ = nullptr;
            other.status_ = ArrayStatus::Empty;
        }

        // move operator=
        ArrayBase& operator=(ArrayBase&& other) {
            if (this == &other) {
                return *this;
            }

            DeleteArray();
            shape_ = std::move(other.shape_);
            size_ = other.size_;
            ptr_raw_data_ = other.ptr_raw_data_;
            status_ = other.status_;

            other.size_ = 0;
            other.ptr_raw_data_ = nullptr;
            other.status_ = ArrayStatus::Empty;

            return *this;
        }

        virtual ~ArrayBase() {
            DeleteArray();
        }

        inline const std::vector<types::Size>& Shape() const { return shape_; }
        inline types::Size Size() const { return size_; }

        inline T* Data() { return ptr_raw_data_; }
        inline const T* Data() const { return ptr_raw_data_; }

        inline T* Begin() { return ptr_raw_data_; }
        inline const T* Begin() const { return ptr_raw_data_; }

        inline T* End() { return ptr_raw_data_ + size_; }
        inline const T* End() const { return ptr_raw_data_ + size_; }

        inline bool IsEmpty() const { return status_ == ArrayStatus::Empty; }
        inline bool IsAllocated() const { return status_ == ArrayStatus::Allocated; }

        virtual types::Size  NumDimensions() const = 0;

        inline bool HasSameShape(const ArrayBase& other) const {
            return shape_ == other.shape_;
        }

        void ResizeLike(const ArrayBase& other) {
            Resize(other.shape_);
        }

        void Fill(const T& value) {
            if (IsAllocated()) {
                std::fill(ptr_raw_data_, ptr_raw_data_ + size_, value);
            }
        }

        void Zero() {
            if (IsAllocated()) {
                std::fill(ptr_raw_data_, ptr_raw_data_ + size_, static_cast<T>(0));
            }
        }

        void Ones() {
            if (IsAllocated()) {
                std::fill(ptr_raw_data_, ptr_raw_data_ + size_, static_cast<T>(1));
            }
        }

        void Swap(ArrayBase& other) noexcept {
            if (!HasSameShape(other)) {
                throw std::invalid_argument("Swap: shape mismatch.");
            }
            std::swap(ptr_raw_data_, other.ptr_raw_data_);
        }

        bool CheckNaN() const {
            if (IsEmpty()) return false;
            for (types::Index i = 0; i < size_; ++i) {
                if (std::isnan(static_cast<double>(ptr_raw_data_[i]))) {
                    return true;
                }
            }
            return false;
        }

        bool CheckFinite() const {
            if (IsEmpty()) return true;
            for (types::Size i = 0; i < size_; ++i) {
                if (!std::isfinite(static_cast<double>(ptr_raw_data_[i]))) {
                    return false;
                }
            }
            return true;
        }

        Array1D<T> Flatten() const {
            Array1D<T> flat(size_);
            if (IsAllocated()) {
                std::copy(ptr_raw_data_, ptr_raw_data_ + size_, flat.Begin());
            }
            return flat;
        }

        void FlattenInto(Array1D<T>& out_flat) const {
            out_flat.Resize(size_);
            if (IsAllocated()) {
                std::copy(ptr_raw_data_, ptr_raw_data_ + size_, out_flat.Begin());
            }
        }

    protected:

        std::vector<types::Size> shape_;
        types::Size size_;
        T* ptr_raw_data_;
        ArrayStatus status_;

        void AllocateArray() {
            if (IsEmpty() && size_ > 0) {
                ptr_raw_data_ = new T[size_];
                status_ = ArrayStatus::Allocated;
            }
        }

        void DeleteArray() {
            if (IsAllocated()) {
                delete[] ptr_raw_data_;
                ptr_raw_data_ = nullptr;
                std::fill(shape_.begin(), shape_.end(), 0);
                size_ = 0;
                status_ = ArrayStatus::Empty;
            }
        }

        types::Size ComputeSize(std::vector<types::Size>& shape) {
            if (shape.empty()) return 0;
            types::Size size = 1;
            for (types::Size dim : shape) {
                size *= dim;
            }
            return size;
        }

        void Resize(const std::vector<types::Size>& shape) {
            if (IsEmpty()) {
                shape_ = shape;
                size_ = ComputeSize(shape_);
                AllocateArray();
            } else if (shape_ != shape) {
                DeleteArray();
                shape_ = shape;
                size_ = ComputeSize(shape_);
                AllocateArray();
            }
        }
    };
}

#endif /* ARRAY_BASE_HPP */