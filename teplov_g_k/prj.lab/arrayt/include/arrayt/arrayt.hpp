#ifndef LIB_ARRAYT_HPP
#define LIB_ARRAYT_HPP

#include <iosfwd>
#include <iostream>
#include <cstdint>
#include <exception>
#include <algorithm>

template<typename T>
class ArrayT{
public:
    ArrayT();
    ArrayT(const ArrayT<T>&);
    ArrayT(const std::ptrdiff_t sizeInp, T num);
    explicit ArrayT(const std::ptrdiff_t len);

    ~ArrayT();

    T& operator[](std::ptrdiff_t index);
    const T& operator[](std::ptrdiff_t index) const;

    void insert(std::ptrdiff_t i, T value);
    void resize(std::ptrdiff_t new_size);
    void remove(std::ptrdiff_t i);
    void reserve(std::ptrdiff_t newCapacity_);

    std::ptrdiff_t ssize() const noexcept;

    ArrayT<T>& operator=(const ArrayT<T>& rhs);

    std::ostream& writeTo(std::ostream& ostrm) const;
    /*std::istream& readFrom(std::istream& istrm);*/

public:
    std::ptrdiff_t capacity_;
    T* data_;
    std::ptrdiff_t size_;
    static const char cmm{ ',' };
};

template<typename T>
ArrayT<T>::ArrayT() {
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
}

template<typename T>
ArrayT<T>::ArrayT(const ArrayT<T>& other):size_(other.size_), capacity_(other.capacity_), data_(nullptr){
    if(this == &other){
        return;
    }
    data_ = new T[capacity_];
    if(other.data_ == nullptr){
        data_ = nullptr;
    }
    else{
        std::copy(other.data_, other.data_ + other.size_, data_);
    }
}

template<typename T>
ArrayT<T>::ArrayT(std::ptrdiff_t sizeInp, T num) {
    if (sizeInp < 0) {
        throw std::out_of_range("Index out of range");
    }
    size_ = sizeInp;
    capacity_ = sizeInp;
    data_ = new T[capacity_];
    for (std::ptrdiff_t i = 0; i < ssize(); ++i) {
        data_[i] = num;
    }
}

template<typename T>
ArrayT<T>::ArrayT(std::ptrdiff_t sizeInp) {
    if (sizeInp < 0) {
        throw std::out_of_range("Index out of range");
    }
    size_ = sizeInp;
    capacity_ = sizeInp;
    data_ = new T[capacity_];
    for (std::ptrdiff_t i = 0; i < ssize(); ++i) {
        data_[i] = 0;
    }
}

template<typename T>
void ArrayT<T>::reserve(std::ptrdiff_t newCapacity_) {
    capacity_ = newCapacity_;
    if (capacity_ < ssize()) {
        size_ = capacity_;
        return;
    }
    T* newMemory_ = new T[capacity_];
    if (data_ == nullptr) {
        data_ = nullptr;
    }
    else {
        std::copy(data_, data_ + ssize(), newMemory_);
    }
    for (std::ptrdiff_t i = ssize(); i < capacity_; ++i) {
        newMemory_[i] = 0;
    }
    delete[] data_;
    data_ = newMemory_;
}

template<typename T>
void ArrayT<T>::resize(std::ptrdiff_t sizeInp) {
    if (sizeInp <= 0) {
        throw std::out_of_range("Size must be positive");
    }
    if (sizeInp > capacity_) {
        reserve(sizeInp);
    }
    if (sizeInp > ssize()) {
        for (std::ptrdiff_t i = ssize(); i < sizeInp; ++i) {
            data_[i] = 0;
        }
    }
    size_ = sizeInp;
}

template<typename T>
ArrayT<T>::~ArrayT()
{
    delete[] data_;
}

template<typename T>
T& ArrayT<T>::operator[] (std::ptrdiff_t index) {
    if ((index < 0) || (index >= ssize())) {
        throw std::out_of_range("Index is out of acceptable area");
    }
    return data_[index];
}

template<typename T>
const T& ArrayT<T>::operator[] ( std::ptrdiff_t index) const {
    if ((index < 0) || (index >= ssize())) {
        throw std::out_of_range("Index is out of acceptable area");
    }
    return data_[index];
}

template<typename T>
std::ptrdiff_t ArrayT<T>::ssize() const noexcept {
    return size_;
};

template<typename T>
void ArrayT<T>::remove(std::ptrdiff_t i) {
    if ((i < 0) || (i >= ssize())) {
        throw std::out_of_range("index out of range");
    }
    for (std::ptrdiff_t start = i + 1; i < ssize(); ++start) {
        data_[start-1] = data_[start];
    }
    resize(ssize() - 1);
}

template<typename T>
void ArrayT<T>::insert(std::ptrdiff_t i, T value) {
    if (i < 0 || i > ssize()) {
        throw std::out_of_range("index must be larger 0");
    }
    resize(ssize() +1);
    for (std::ptrdiff_t index = ssize() - 1; index > i; --index) {
        data_[index] = data_[index - 1];
    }
    data_[i] = value;
}

template<typename T>
ArrayT<T>& ArrayT<T>::operator=(const ArrayT<T>& other) {
    if(this == &other){
        return *this;
    }
    size_ = other.size_;
    capacity_ = other.capacity_;
    delete[] data_;
    data_ = new T[capacity_];
    for (std::ptrdiff_t i = 0; i < ssize(); ++i) {
        new (data_ + i) T(other.data_[i]);
    }
    return *this;
}

template<typename T>
std::ostream& operator<<(std::ostream& ostrm, const ArrayT<T>& rhs) {
    return rhs.writeTo(ostrm);
}

template<typename T>
std::ostream& ArrayT<T>::writeTo(std::ostream& ostrm) const
{
    ostrm << '[';
    for (std::ptrdiff_t i = 0; i < ssize() - 1; ++i) {
        ostrm << data_[i] << cmm;
    }
    ostrm << data_[size_ - 1] << ']';
    return ostrm;
}
#endif //LIB_ARRAYT_HPP
