#ifndef ARRAY_BASE_HPP_
#define ARRAY_BASE_HPP_

#include <vector>
#include <algorithm>
#include <initializer_list>
#include <limits>
#include <cmath>

#include "array1d.hpp"


namespace array {
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

        // #######################
        // Constructors
        // #######################
        ArrayBase() noexcept : shape_({}), size_(0), ptr_raw_data_(nullptr), status_(ArrayStatus::Empty) { }

        ArrayBase(std::initializer_list<std::size_t> shape)
        : shape_(shape), size_(ComputeSize(shape_)), ptr_raw_data_(nullptr), status_(ArrayStatus::Empty) {
            AllocateArray();
        }

        ArrayBase(std::initializer_list<std::size_t> shape, const T value)
        : shape_(shape), size_(ComputeSize(shape_)), ptr_raw_data_(nullptr), status_(ArrayStatus::Empty) {
            AllocateArray();
            Fill(value);
        }

        // Copy constructor
        ArrayBase(const ArrayBase& other) noexcept
            : shape_(other.shape_), size_(other.size_), ptr_raw_data_(nullptr), status_(ArrayStatus::Empty) {
            AllocateArray();
            if (other.IsAllocated()) {
                std::copy(other.Begin(), other.End(), ptr_raw_data_);
            }
        }

        // Copy assignment
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

        // Move constructor
        ArrayBase(ArrayBase&& other) noexcept
        : shape_(std::move(other.shape_)), size_(other.size_), ptr_raw_data_(other.ptr_raw_data_), status_(other.status_) {
            other.size_ = 0;
            other.ptr_raw_data_ = nullptr;
            other.status_ = ArrayStatus::Empty;
        }

        // Move assignment
        ArrayBase& operator=(ArrayBase&& other) noexcept {
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

        inline const std::vector<std::size_t>& Shape() const noexcept { return shape_; }
        inline std::size_t Size() const noexcept { return size_; }

        inline T* Data() noexcept { return ptr_raw_data_; }
        inline const T* Data() const noexcept { return ptr_raw_data_; }

        inline T* Begin() noexcept { return ptr_raw_data_; }
        inline const T* Begin() const noexcept { return ptr_raw_data_; }

        inline T* End() noexcept { return ptr_raw_data_ + size_; }
        inline const T* End() const noexcept { return ptr_raw_data_ + size_; }

        inline bool IsEmpty() const noexcept { return status_ == ArrayStatus::Empty; }
        inline bool IsAllocated() const noexcept { return status_ == ArrayStatus::Allocated; }

        virtual std::size_t  NumDimensions() const noexcept = 0;

        inline bool HasSameShape(const ArrayBase& other) const noexcept {
            return shape_ == other.shape_;
        }

        void ResizeLike(const ArrayBase& other) {
            Resize(other.shape_);
        }

        void Fill(const T& value) {
            if (IsAllocated()) {
                std::fill(Begin(), End(), value);
            }
        }

        void Zero() {
            if (IsAllocated()) {
                std::fill(Begin(), End(), static_cast<T>(0));
            }
        }

        void Ones() {
            if (IsAllocated()) {
                std::fill(Begin(), End(), static_cast<T>(1));
            }
        }

        void Swap(ArrayBase& other) {
            if (!HasSameShape(other)) {
                throw std::invalid_argument("Swap: shape mismatch.");
            }
            std::swap(ptr_raw_data_, other.ptr_raw_data_);
        }

        bool CheckNaN() const {
            static_assert(std::is_floating_point<T>::value, "CheckNaN requires floating point type");
            if (IsEmpty()) return false;
            for (std::size_t i = 0; i < size_; ++i) {
                if (std::isnan(static_cast<double>(ptr_raw_data_[i]))) {
                    return true;
                }
            }
            return false;
        }

        bool CheckFinite() const {
            static_assert(std::is_floating_point<T>::value, "CheckFinite requires floating point type");
            if (IsEmpty()) return true;
            for (std::size_t i = 0; i < size_; ++i) {
                if (!std::isfinite(static_cast<double>(ptr_raw_data_[i]))) {
                    return false;
                }
            }
            return true;
        }

        Array1D<T> Flatten() const {
            Array1D<T> flat(size_);
            if (IsAllocated()) {
                std::copy(Begin(), End(), flat.Begin());
            }
            return flat;
        }

        void FlattenInto(Array1D<T>& out_flat) const {
            out_flat.Resize(size_);
            if (IsAllocated()) {
                std::copy(Begin(), End(), out_flat.Begin());
            }
        }

    protected:
        std::vector<std::size_t> shape_;
        std::size_t size_;
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

        std::size_t ComputeSize(std::vector<std::size_t>& shape) {
            if (shape.empty()) return 0;
            std::size_t size = 1;
            for (std::size_t dim : shape) {
                size *= dim;
            }
            return size;
        }

        void Resize(const std::vector<std::size_t>& shape) {
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

#endif /* ARRAY_BASE_HPP_ */