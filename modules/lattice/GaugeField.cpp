#include "lattice/GaugeField.h"


// SU(3) constructor
template <typename T>
SU_3<T>::SU_3() : data({}) {}

// SU(3) constructor with values
template <typename T>
SU_3<T>::SU_3(const std::array<std::complex<T>, 9>& values) : data(values) {}

// SU(3) copy constructor
template <typename T>
SU_3<T>::SU_3(const SU_3<T>& su3_mat) : data(su3_mat.data) {}

// SU(3) move constructor
template <typename T>
SU_3<T>::SU_3(SU_3<T>&& su3_mat) noexcept : data(std::move(su3_mat.data)) {}

// Accessors
template <typename T>
std::complex<T>& SU_3<T>::operator()(size_t row, size_t col) {
    return data[row * 3 + col];
}

template <typename T>
const std::complex<T>& SU_3<T>::operator()(size_t row, size_t col) const {
    return data[row * 3 + col];
}

// U + V
template <typename T>
SU_3<T> SU_3<T>::operator+(const SU_3<T>& su3_mat) const {
    SU_3<T> result;
    for (size_t i = 0; i < 9; ++i) {
        result.data[i] = data[i] + su3_mat.data[i];
    }
    return result;
}

// U - V
template <typename T>
SU_3<T> SU_3<T>::operator-(const SU_3<T>& su3_mat) const {
    SU_3<T> result;
    for (size_t i = 0; i < 9; ++i) {
        result.data[i] = data[i] - su3_mat.data[i];
    }
    return result;
}

// U * V
template <typename T>
SU_3<T> SU_3<T>::operator*(const SU_3<T>& su3_mat) const {
    SU_3<T> result;

    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            result(i, j) = data[i * 3 + 0] * su3_mat(0, j) +
                        data[i * 3 + 1] * su3_mat(1, j) +
                        data[i * 3 + 2] * su3_mat(2, j);
        }
    }

    return result;
}


