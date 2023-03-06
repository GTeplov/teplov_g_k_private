#include <sstream>
#include <numeric>
#include <rational/rational.hpp>

inline std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs)
{
    return rhs.writeTo(ostrm);
}

inline std::istream& operator>>(std::istream& istrm, Rational& rhs)
{
    return rhs.readFrom(istrm);
}

Rational::Rational(const int numerator)
    : Rational(numerator, 1)
{
}

Rational::Rational(const int numerator, const int denumerator) {
    if (denumerator == 0)
        throw std::runtime_error("division by zero");
    else {
        num_ = std::abs(numerator) / std::gcd(std::abs(numerator), std::abs(denumerator));
        den_ = std::abs(denumerator) / std::gcd(std::abs(numerator), std::abs(denumerator));
        if ((num_ < 0) != (den_ < 0))
            num_ = -num_;
    }
}

Rational& Rational::operator+=(const Rational& rhs) {
    den_ = std::lcm(den_, rhs.den_);
    num_ = num_ * (std::lcm(den_, rhs.den_) / den_) + rhs.num_ * (std::lcm(den_, rhs.den_) / rhs.den_);
    return *this;
}

Rational& Rational::operator-=(const Rational& rhs) {
    den_ = std::lcm(den_, rhs.den_);
    num_ = num_ * (std::lcm(den_, rhs.den_) / den_) - rhs.num_ * (std::lcm(den_, rhs.den_) / rhs.den_);
    return *this;
}

Rational& Rational::operator*=(const Rational& rhs) {
    den_ *= rhs.den_;
    num_ *= rhs.num_;
    num_ = std::abs(num_) / std::gcd(std::abs(num_), std::abs(den_));
    den_ = std::abs(den_) / std::gcd(std::abs(num_), std::abs(den_));
    return *this;
}

Rational& Rational::operator/=(const Rational& rhs) {
    den_ *= rhs.den_;
    num_ *= rhs.num_;
    num_ = std::abs(num_) / std::gcd(std::abs(num_), std::abs(den_));
    den_ = std::abs(den_) / std::gcd(std::abs(num_), std::abs(den_));
    return *this;
}

bool Rational::operator==(const Rational& other) const noexcept {
    return (num_ == other.num_ && den_ == other.den_);
}

bool Rational::operator!=(const Rational& other) const noexcept {
    return !(*this == other);
}

bool Rational::operator>(const Rational& other) const noexcept {
    return (num_ * other.den_ > den_ * other.num_);
}

bool Rational::operator<(const Rational& other) const noexcept {
    return (num_ * other.den_ < den_ * other.num_);
}

bool Rational::operator>=(const Rational& other) const noexcept {
    return (*this > other || *this == other);
}

bool Rational::operator<=(const Rational& other) const noexcept {
    return (*this < other || *this == other);
}

Rational Rational::operator-() const noexcept {
    return Rational(-num_, den_);
}

Rational::operator bool() const noexcept {
    return (num_ != 0);
}

std::istream& Rational::read_from(std::istream& istrm) noexcept {
    int num, den;
    char slash;
    istrm >> num >> slash >> den;
    if (istrm.good()) {
        num_ = num;
        den_ = den;
        normalize();
    }
    return istrm;
}

std::ostream& Rational::write_to(std::ostream& ostrm) const noexcept {
    ostrm << num_ << delimiter_ << den_;
    return ostrm;
}

void Rational::normalize() noexcept {
    if (den_ < 0) {
        num_ = -num_;
        den_ = -den_;
    }
    int gcd = std::gcd(num_, den_);
    num_ /= gcd;
    den_ /= gcd;
}
