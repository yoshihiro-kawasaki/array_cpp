#ifndef ARRAY_HPP
#define ARRAY_HPP

#include "types.hpp"
#include <vector>
#include <algorithm>

namespace array
{
    enum class ArrayStatus {
        Empty,
        Allocated
    };

    using ArrayShape = std::vector<types::Size>;

    template <typename T>
    class Array {
    public:
        Array() : size_(0), shape_({}), ndim_(0), pdata_(nullptr), status_(ArrayStatus::Empty) { }

        Array(const types::Size n1)
        : shape_({n1}), ndim_(1), pdata_(nullptr), status_(ArrayStatus::Empty) {
            size_ = ComputeSize(shape_);
            AllocateArray();
        }

        Array(const types::Size n1, const types::Size n2)
        : shape_({n1, n2}), ndim_(2), pdata_(nullptr), status_(ArrayStatus::Empty) {
            size_ = ComputeSize(shape_);
            AllocateArray();
        }

        Array(const types::Size n1, const types::Size n2, const types::Size n3)
        : shape_({n1, n2, n3}), ndim_(3), pdata_(nullptr), status_(ArrayStatus::Empty) {
            size_ = ComputeSize(shape_);
            AllocateArray();
        }

        Array(const types::Size n1, const types::Size n2, const types::Size n3, const types::Size n4)
        : shape_({n1, n2, n3, n4}), ndim_(4), pdata_(nullptr), status_(ArrayStatus::Empty) {
            size_ = ComputeSize(shape_);
            AllocateArray();
        }

        Array(const types::Size n1, const types::Size n2, const types::Size n3, const types::Size n4, const types::Size n5)
        : shape_({n1, n2, n3, n4, n5}), ndim_(5), pdata_(nullptr), status_(ArrayStatus::Empty) {
            size_ = ComputeSize(shape_);
            AllocateArray();
        }

        Array(const types::Size n1, const types::Size n2, const types::Size n3, const types::Size n4, const types::Size n5, const types::Size n6)
        : shape_({n1, n2, n3, n4, n5, n6}), ndim_(6), pdata_(nullptr), status_(ArrayStatus::Empty) {
            size_ = ComputeSize(shape_);
            AllocateArray();
        }

        Array(const ArrayShape& shape)
        : shape_(shape), ndim_(shape.size()), pdata_(nullptr), status_(ArrayStatus::Empty) {
            size_ = ComputeSize(shape_);
            AllocateArray();
        }

        // copy constructor
        Array(const Array& other)
        : shape_(other.shape_), size_(other.size_), ndim_(other.ndim_), pdata_(nullptr), status_(ArrayStatus::Empty) {
            std::cout << "copy" << std::endl;
            AllocateArray();
            if (other.IsAllocated()) {
                std::copy(other.Begin(), other.End(), pdata_);
            }
        }

        // copy operator
        Array& operator=(const Array& other) {
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
                std::copy(other.Begin(), other.End(), pdata_);
            }

            return *this;
        }

        // move constructor
        Array(Array&& other) noexcept
        : shape_(std::move(other.shape_)), size_(other.size_), ndim_(other.ndim_), pdata_(nullptr), status_(other.status_) {
            other.size_ = 0;
            other.shape_.clear();
            other.ndim_ = 0;
            other.pdata_ = nullptr;
            other.status_ = ArrayStatus::Empty;
        }

        // move operator
        Array& operator=(Array&& other) {
            if (this == &other) {
                return *this;
            }

            DeleteArray();
            shape_ = std::move(other.shape_);
            size_ = other.size_;
            ndim_ = other.ndim_;
            pdata_ = other.pdata_;
            status_ = other.status_;

            other.size_ = 0;
            other.shape_.clear();
            other.ndim_ = 0;
            other.pdata_ = nullptr;
            other.status_ = ArrayStatus::Empty;

            return *this;
        }

        ~Array() { DeleteArray(); }

        inline types::Size Size() const { return size_; }
        inline const ArrayShape& Shape() const { return shape_; }
        inline types::Size Ndim() const { return ndim_; }

        inline types::Size Dim1() const { return shape_[0]; }
        inline types::Size Dim2() const { return shape_[1]; }
        inline types::Size Dim3() const { return shape_[2]; }
        inline types::Size Dim4() const { return shape_[3]; }
        inline types::Size Dim5() const { return shape_[4]; }
        inline types::Size Dim6() const { return shape_[5]; }

        inline T* Data() { return pdata_; }
        inline const T* Data() const { return pdata_; }

        inline T* Begin() { return pdata_; }
        inline const T* Begin() const { return pdata_; }

        inline T* End() { return pdata_ + size_; }
        inline const T* End() const { return pdata_ + size_; }

        inline bool IsEmpty() { return status_ == ArrayStatus::Empty; }
        inline bool IsAllocated() { return status_ == ArrayStatus::Allocated; }

        inline bool HasSameShape(const Array& other) const {
            return shape_ == other.shape_;
        }

        inline T& operator()(const types::Index i) {
            return pdata_[i];
        }
        inline const T& operator()(const types::Index i) const {
            return pdata_[i];
        }

        inline T& operator()(const types::Index i, const types::Index j) {
            return pdata_[i * shape_[1] + j];
        }
        inline const T& operator()(const types::Index i, const types::Index j) const {
            return pdata_[i * shape_[1] + j];
        }

        inline T& operator()(const types::Index i, const types::Index j, const types::Index k) {
            return pdata_[(i * shape_[1] + j) * shape_[2] + k];
        }
        inline const T& operator()(const types::Index i, const types::Index j, const types::Index k) const {
            return pdata_[(i * shape_[1] + j) * shape_[2] + k];
        }

        inline T& operator()(const types::Index i, const types::Index j, const types::Index k, const types::Index l) {
            return pdata_[((i * shape_[1] + j) * shape_[2] + k) * shape_[3] + l];
        }
        inline const T& operator()(const types::Index i, const types::Index j, const types::Index k, const types::Index l) const {
            return pdata_[((i * shape_[1] + j) * shape_[2] + k) * shape_[3] + l];
        }

        inline T& operator()(const types::Index i, const types::Index j, const types::Index k, const types::Index l, const types::Index m) {
            return pdata_[(((i * shape_[1] + j) * shape_[2] + k) * shape_[3] + l) * shape_[4] + m];
        }
        inline const T& operator()(const types::Index i, const types::Index j, const types::Index k, const types::Index l, const types::Index m) const {
            return pdata_[(((i * shape_[1] + j) * shape_[2] + k) * shape_[3] + l) * shape_[4] + m];
        }

        inline T& operator()(const types::Index i, const types::Index j, const types::Index k, const types::Index l, const types::Index m, const types::Index n) {
            return pdata_[((((i * shape_[1] + j) * shape_[2] + k) * shape_[3] + l) * shape_[4] + m) * shape_[5] + n];
        }
        inline const T& operator()(const types::Index i, const types::Index j, const types::Index k, const types::Index l, const types::Index m, const types::Index n) const {
            return pdata_[((((i * shape_[1] + j) * shape_[2] + k) * shape_[3] + l) * shape_[4] + m) * shape_[5] + n];
        }

        void Fill(const T& value) {
            if (IsAllocated()) {
                std::fill(pdata_, pdata_ + size_, value);
            }
        }

        void Zero() {
            if (IsAllocated()) {
                std::fill(pdata_, pdata_ + size_, static_cast<T>(0));
            }
        }

        void One() {
            if (IsAllocated()) {
                std::fill(pdata_, pdata_ + size_, static_cast<T>(1));
            }
        }

        void Swap(Array& other) noexcept {
            if (HasSameShape(other)) {
                std::swap(pdata_, other.pdata_);
            }
        }

        void Resize(const types::Size n1) {
            ArrayShape shape_new = {n1};
            ResizeImpl(shape_new);
        }

        void Resize(const types::Size n1, const types::Size n2) {
            ArrayShape shape_new = {n1, n2};
            ResizeImpl(shape_new);
        }

        void Resize(const types::Size n1, const types::Size n2, const types::Size n3) {
            ArrayShape shape_new = {n1, n2, n3};
            ResizeImpl(shape_new);
        }

        void Resize(const types::Size n1, const types::Size n2, const types::Size n3, const types::Size n4) {
            ArrayShape shape_new = {n1, n2, n3, n4};
            ResizeImpl(shape_new);
        }

        void Resize(const types::Size n1, const types::Size n2, const types::Size n3, const types::Size n4, const types::Size n5) {
            ArrayShape shape_new = {n1, n2, n3, n4, n5};
            ResizeImpl(shape_new);
        }

        void Resize(const types::Size n1, const types::Size n2, const types::Size n3, const types::Size n4, const types::Size n5, const types::Size n6) {
            ArrayShape shape_new = {n1, n2, n3, n4, n5, n6};
            ResizeImpl(shape_new);
        }

        void Resize(const ArrayShape& shape) {
            ResizeImpl(shape);
        }

        void Flatten() {
            if (IsAllocated()) {
                shape_ = {size_};
                ndim_ = 1;
            }
        }

        Array Flatten() const {
            Array<T> flat(size_);
            if (IsAllocated()) {
                std::copy(pdata_, pdata_ + size_, flat.pdata_);
            }
            return flat;
        }

        void FlattenInto(Array& out_flat) const {
            out_flat.Resize(size_);
            if (IsAllocated()) {
                std::copy(pdata_, pdata_ + size_, out_flat.pdata_);
            }
        }

    private:
        
        void AllocateArray() {
            if (IsEmpty() && size_ > 0) {
                pdata_ = new T[size_];
                status_ = ArrayStatus::Allocated;
            }
        }

        void DeleteArray() {
            if (IsAllocated()) {
                delete[] pdata_;
                pdata_ = nullptr;
                size_ = 0;
                shape_.clear();
                ndim_ = 0;
                status_ = ArrayStatus::Empty;
            }
        }

        types::Size ComputeSize(ArrayShape& shape) {
            if (shape.empty()) return 0;
            types::Size size = 1;
            for (types::Size dim : shape) {
                size *= dim;
            }
            return size;
        }

        void ResizeImpl(const ArrayShape& shape) {
            if (IsEmpty()) {
                shape_ = shape;
                size_ = ComputeSize(shape_);
                ndim_ = shape_.size();
                AllocateArray();
            } else if (shape_ != shape) {
                DeleteArray();
                shape_ = shape;
                size_ = ComputeSize(shape_);
                ndim_ = shape_.size();
                AllocateArray();
            }
        }

        types::Size size_;
        ArrayShape shape_;
        types::Size ndim_;
        T* pdata_;
        ArrayStatus status_;
    };
}

#endif /* ARRAY_HPP */