#include <arrayd/arrayd.hpp>
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>

ArrayD::ArrayD() {
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
}

ArrayD::ArrayD(const ArrayD& other):size_(other.size_), capacity_(other.capacity_), data_(nullptr){
    if(this == &other){
        return;
    }
    data_ = new double[capacity_];
    if(other.data_ == nullptr){
        data_ = nullptr;
    }
    else{
        std::copy(other.data_, other.data_ + other.size_, data_);
    }
}
ArrayD::ArrayD(const std::ptrdiff_t sizeInp, const double num) {
    if (sizeInp < 0) {
        throw std::out_of_range("Index out of range");
    }
    size_ = sizeInp;
    capacity_ = sizeInp;
    data_ = new double[capacity_];
    for (std::ptrdiff_t i = 0; i < ssize(); ++i) {
        data_[i] = num;
    }
}
ArrayD::ArrayD(const std::ptrdiff_t sizeInp) {
    if (sizeInp < 0) {
        throw std::out_of_range("Index out of range");
    }
    size_ = sizeInp;
    capacity_ = sizeInp;
    data_ = new double[capacity_];
    for (std::ptrdiff_t i = 0; i < ssize(); ++i) {
        data_[i] = 0;
    }
}
void ArrayD::reserve(const std::ptrdiff_t newCapacity_) {
    capacity_ = newCapacity_;
    if (capacity_ < ssize()) {
        size_ = capacity_;
        return;
    }
    double* newMemory_ = new double[capacity_];
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
void ArrayD::resize(const std::ptrdiff_t sizeInp) {
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


ArrayD::~ArrayD()
{
    delete[] data_;
}

double& ArrayD::operator[] (const std::ptrdiff_t index) {
    if ((index < 0) || (index >= ssize())) {
        throw std::out_of_range("Index is out of acceptable area");
    }
    return data_[index];
}
const double& ArrayD::operator[] (const std::ptrdiff_t index) const {
    if ((index < 0) || (index >= ssize())) {
        throw std::out_of_range("Index is out of acceptable area");
    }
        return data_[index];
}
std::ptrdiff_t ArrayD::ssize() const noexcept {
    return size_;
};


void ArrayD::remove(const std::ptrdiff_t i) {
    if ((i < 0) || (i >= ssize())) {
        throw std::out_of_range("index out of range");
    }
    for (std::ptrdiff_t start = i + 1; i < ssize(); ++start) {
        data_[start-1] = data_[start];
    }
    resize(ssize() - 1);
}


void ArrayD::insert(const std::ptrdiff_t i, const double value) {
    if (i < 0 || i > ssize()) {
        throw std::out_of_range("index must be larger 0");
    }
    resize(ssize() +1);
    for (std::ptrdiff_t index = ssize() - 1; index > i; --index) {
        data_[index] = data_[index - 1];
    }
    data_[i] = value;
}

ArrayD& ArrayD::operator=(const ArrayD& other) {
    if(this == &other){
        return *this;
    }
    size_ = other.size_;
    capacity_ = other.capacity_;
    delete[] data_;
    data_ = new double[capacity_];
    for (std::ptrdiff_t i = 0; i < ssize(); ++i) {
        new (data_ + i) double (other.data_[i]);
    }
    return *this;
}

std::ostream& operator<<(std::ostream& ostrm, const ArrayD& rhs) {
    return rhs.writeTo(ostrm);
}

std::ostream& ArrayD::writeTo(std::ostream& ostrm) const
{
    ostrm << '[';
    for (std::ptrdiff_t i = 0; i < ssize() - 1; ++i) {
        ostrm << data_[i] << cmm;
    }
    ostrm << data_[size_ - 1] << ']';
    return ostrm;
}