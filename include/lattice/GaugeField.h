#ifndef GAUGEFIELD_H
#define GAUGEFIELD_H

#include <complex>
#include <iostream>


// Define the SU(3) class via the fundamental representation.
template <typename T>
class SU_3 {
public:
    // Constructor
    SU_3();
    SU_3(const std::array<std::complex<T>, 9>& values);  // Constructor with values

    // Copy constructor
    SU_3(const SU_3<T>& su3_mat);

    // Move constructor
    SU_3(SU_3<T>&& su3_mat) noexcept;

    // Accessor
    std::complex<T>& operator()(size_t row, size_t col);
    const std::complex<T>& operator()(size_t row, size_t col) const;

    // U * V operations
    SU_3<T> operator+(const SU_3<T>& su3_mat) const;
    SU_3<T> operator-(const SU_3<T>& su3_mat) const;
    SU_3<T> operator*(const SU_3<T>& su3_mat) const;

    // U * \vec{v} multiplication
    std::array<std::complex<T>, 3> operator*(const std::array<std::complex<T>, 3>& vec) const;

    // Scalar multiplication
    SU_3<T> operator*(const std::complex<T>& scalar) const;

    // Hermitian conjugation (dagger operation)
    SU_3<T> adjoint() const;  // Returns the adjoint of the matrix as copy value.

    // Print the matrix
    void print() const;
private:
    std::array<std::complex<T>, 9> data;
};


// TODO: Define the SU(3) class via the adjoint representation? This would require changing names.



// Define the GaugeField class
template <typename T>
class GaugeField : public LatticeField<SU_3<T>> {
public:
    SU_3<T> get_link(size_t i0, size_t i1, size_t i2, size_t i3, size_t mu) const;
    std::complex<T> get_rect(size_t i0, size_t i1, size_t i2, size_t i3) const;
    std::complex<T> get_plaquette(size_t i0, size_t i1, size_t i2, size_t i3) const;

    void set_link(size_t i0, size_t i1, size_t i2, size_t i3, size_t mu, const SU_3<T>& link);
};

#endif // GAUGEFIELD_H
