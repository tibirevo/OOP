#include "L3_Gagea_Tiberiu_Problem1_complex.h"
#include <cmath>

Complex::Complex(double re, double im) : real(re), imaginary(im){

}

double Complex::get_real() const {
    return real;
}

double Complex::get_imaginary() const {
    return imaginary;
}

Complex Complex::add(const Complex &other) const {
    double real_nou = this->real + other.real;
    double imaginar_nou = this->imaginary + other.imaginary;
    return Complex(real_nou, imaginar_nou);
}

Complex Complex::subtract(const Complex &other) const {
    double real_nou = this->real - other.real;
    double imaginar_nou = this->imaginary - other.imaginary;
    return Complex(real_nou, imaginar_nou);
}

Complex Complex::multiply(const Complex &other) const {
    double real_nou = (this->real * other.real) - (this->imaginary * other.imaginary);
    double imaginar_nou = (this->real * other.imaginary) + (this->imaginary * other.real);
    return Complex(real_nou, imaginar_nou);
}

Complex Complex::divide(const Complex &other) const {
    double numitor = (other.real * other.real) + (other.imaginary * other.imaginary);
    double real_nou = ((this->real * other.real) + (this->imaginary * other.imaginary)) / numitor;
    double imaginar_nou = ((this->imaginary * other.real) - (this->real * other.imaginary)) / numitor;
    return Complex(real_nou, imaginar_nou);
}

Complex Complex::operator+(const Complex &other) const {
    return this->add(other);
}

Complex Complex::operator-(const Complex &other) const {
    return this->subtract(other);
}

Complex Complex::operator*(const Complex &other) const {
    return this->multiply(other);
}

Complex Complex::operator/(const Complex &other) const {
    return this->divide(other);
}

bool Complex::operator==(const Complex &other) const {
    const double EPSILON = 1e-9;
    bool real_egal = std::abs(this->real - other.real) < EPSILON;
    bool imaginar_egal = std::abs(this->imaginary - other.imaginary) < EPSILON;
    return real_egal && imaginar_egal;
}

bool Complex::operator!=(const Complex &other) const {
    return !(*this == other);
}

double Complex::absolute() const {
    return std::sqrt(real * real + imaginary * imaginary);
}

Complex Complex::conjugate() const {
    return Complex(real, -imaginary);
}

std::pair<double, double> Complex::compute_polar() const {
    double r = this->absolute();
    double theta = std::atan2(imaginary, real);
    return std::make_pair(r, theta);
}

std::string Complex::text() const {
    std::string semn = (imaginary >= 0) ? " + " : " - ";
    return std::to_string(real) + semn + std::to_string(std::abs(imaginary)) + "i";
}

std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << c.text();
    return os;
}