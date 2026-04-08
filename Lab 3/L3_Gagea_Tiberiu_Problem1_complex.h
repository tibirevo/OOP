#pragma once
#include <iostream>
#include <string>
#include <utility>

class Complex {
private:
    double real;
    double imaginary;
public:
    Complex(double re = 0.0, double im = 0.0);
    double get_real() const;
    double get_imaginary() const;
    Complex add(const Complex& other) const;
    Complex subtract(const Complex& other) const;
    Complex multiply(const Complex& other) const;
    Complex divide(const Complex& other) const;

    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;
    bool operator==(const Complex& other) const;
    bool operator!=(const Complex& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Complex& c);

    double absolute() const;
    Complex conjugate() const;
    std::pair<double, double> compute_polar() const;
    std::string text() const;
};


