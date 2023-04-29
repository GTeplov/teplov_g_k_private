#ifndef PROGRAMMING_ARRAYD_HPP
#define PROGRAMMING_ARRAYD_HPP

#include <iosfwd>
#include <cstdint>

class ArrayD{
public:
    ArrayD();
    ArrayD(const ArrayD&);
    ArrayD(const std::ptrdiff_t sizeInp, const double num);

    ~ArrayD();

    double& operator[](std::ptrdiff_t index);
    const double& operator[](std::ptrdiff_t index) const;

    void insert(const std::ptrdiff_t i, const double value);
    void resize(std::ptrdiff_t new_size);
    void reserve(const std::ptrdiff_t newCapacity_);
    void remove(const std::ptrdiff_t i);
    explicit ArrayD(const std::ptrdiff_t len);

    std::ptrdiff_t ssize() const noexcept;

    ArrayD& operator=(const ArrayD& rhs);

    std::ostream& writeTo(std::ostream& ostrm) const;
    /*std::istream& readFrom(std::istream& istrm);*/

public:
    ptrdiff_t capacity_;
    double* data_;
    ptrdiff_t size_;
    static const char cmm{ ',' };
};

std::ostream& operator<<(std::ostream& ostrm, const ArrayD& rhs);
//std::istream& operator>>(std::istream& istrm, ArrayD& rhs);

#endif //PROGRAMMING_ARRAYD_HPP