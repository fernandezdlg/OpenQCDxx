#ifndef SU_3_H
#define SU_3_H

#include <complex>
#include <iostream>
#include <array>


// Define the SU(3) class via the fundamental representation.
template <typename T>
class SU_3 {
public:
    // Constructor
    SU_3() : data({}) {}  // Default constructor

    // Constructor with values
    SU_3(const std::array<std::complex<T>, 9>& values) : data(values) {}

    // Copy constructor
    SU_3(const SU_3<T>& su3_mat) : data(su3_mat.data) {}

    // Move constructor
    SU_3(SU_3<T>&& su3_mat) noexcept : data(std::move(su3_mat.data)) {}

    // Accessors
    std::complex<T>& operator()(size_t row, size_t col) {
        return data[row * 3 + col];
    }
    const std::complex<T>& operator()(size_t row, size_t col) const {
        return data[row * 3 + col];
    }

    // U , V operations
    SU_3<T> operator+(const SU_3<T>& su3_mat) const {
        SU_3<T> result;
        for (size_t i = 0; i < 9; ++i) {
            result.data[i] = data[i] + su3_mat.data[i];
        }
        return result;
    }
    SU_3<T> operator-(const SU_3<T>& su3_mat) const {
        SU_3<T> result;
        for (size_t i = 0; i < 9; ++i) {
            result.data[i] = data[i] - su3_mat.data[i];
        }
        return result;
    }
    SU_3<T> operator*(const SU_3<T>& su3_mat) const {
        SU_3<T> result;
        for (size_t i = 0; i < 3; ++i) {
            for (size_t j = 0; j < 3; ++j) {
                result(i, j) = 0;
                for (size_t k = 0; k < 3; ++k) {
                    result(i, j) += data[i * 3 + k] * su3_mat(k, j);
                }
            }
        }
        return result;
    }

    // U * \vec{v} multiplication
    std::array<std::complex<T>, 3> operator*(const std::array<std::complex<T>, 3>& vec) const {
        std::array<std::complex<T>, 3> result;
        for (size_t i = 0; i < 3; ++i) {
            result[i] = 0;
            for (size_t j = 0; j < 3; ++j) {
                result[i] += data[i * 3 + j] * vec[j];
            }
        }
        return result;
    }

    // Scalar multiplication
    SU_3<T> operator*(const std::complex<T>& scalar) const {
        SU_3<T> result;
        for (size_t i = 0; i < 9; ++i) {
            result.data[i] = data[i] * scalar;
        }
        return result;
    }

    // Hermitian conjugation (dagger operation)
    SU_3<T> adjoint() const {
        SU_3<T> result;
        for (size_t i = 0; i < 3; ++i) {
            for (size_t j = 0; j < 3; ++j) {
                result(i, j) = std::conj(data[3*j + i]);
            }
        }
        return result;
    }

    // Trace
    std::complex<T> trace() const {
        std::complex<T> result = 0;
        for (size_t i = 0; i < 3; ++i) {
            result += data[i * 3 + i];
        }
        return result;
    }

    // Stream
    friend std::ostream& operator<<(std::ostream& os, const SU_3<T>& su3_mat) {
        os << "[";
        for (size_t i = 0; i < 3; ++i) {
            os << "[";
            for (size_t j = 0; j < 3; ++j) {
                os << su3_mat(i, j);
                if (j < 2) {
                    os << ", ";
                }
            }
            os << "]";
            if (i < 2) {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }

    // Print the matrix TODO: check
    void print() const {
        std::cout << *this << "\n";
    }

private:
    std::array<std::complex<T>, 9> data;
};

#endif // SU_3_H
