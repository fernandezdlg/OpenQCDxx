#include "lattice/GaugeField.h"
#include "random/ranlxs.h"
#include "random/ranlxd.h"

/*************************
 * Definitions for SU(3) *
 ************************/

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

// // Stream
// template <typename T>
// std::ostream& operator<<(std::ostream& os, const SU_3<T>& su3_mat) {
//     os << "[";
//     for (size_t i = 0; i < 3; ++i) {
//         os << "[";
//         for (size_t j = 0; j < 3; ++j) {
//             os << su3_mat(i, j);
//             if (j < 2) {
//                 os << ", ";
//             }
//         }
//         os << "]";
//         if (i < 2) {
//             os << ", ";
//         }
//     }
//     os << "]";
//     return os;
// }

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


// U * \vec{v} multiplication
template <typename T>
std::array<std::complex<T>, 3> SU_3<T>::operator*(const std::array<std::complex<T>, 3>& vec) const {
    std::array<std::complex<T>, 3> result;

    for (size_t i = 0; i < 3; ++i) {
        result[i] = data[i] * vec[0] + data[i + 3] * vec[1] + data[i + 6] * vec[2];
    }

    return result;
}


// Scalar multiplication
template <typename T>
SU_3<T> SU_3<T>::operator*(const std::complex<T>& scalar) const {
    SU_3<T> result;
    for (size_t i = 0; i < 9; ++i) {
        result.data[i] = data[i] * scalar;
    }
    return result;
}


// Hermitian conjugation
template <typename T>
SU_3<T> SU_3<T>::adjoint() const {
    SU_3<T> result;
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            result(i, j) = std::conj(data[j * 3 + i]);
        }
    }
    return result;
}


// Trace
template <typename T>
std::complex<T> SU_3<T>::trace() const {
    return data[0] + data[4] + data[8];
}


// Print the matrix
template <typename T>
void SU_3<T>::print() const {
    std::cout << "[";
    for (size_t i = 0; i < 3; ++i) {
        std::cout << "[";
        for (size_t j = 0; j < 3; ++j) {
            std::cout << data[i * 3 + j];
            if (j < 2) {
                std::cout << ", ";
            }
        }
        std::cout << "]";
        if (i < 2) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}



/******************************
 * Definitions for GaugeField *
 *****************************/
// Constructors
template <typename T>
GaugeField<T>::GaugeField(size_t dim0, size_t dim1, size_t dim2, size_t dim3) : LatticeField<std::array<SU_3<T>,4>>(dim0, dim1, dim2, dim3) {}

// FIXME:
// template <typename T>
// GaugeField<T>::GaugeField(size_t dim0, size_t dim1, size_t dim2, size_t dim3, SU_3<T> init_value) : LatticeField<std::array<SU_3<T>,4>>(dim0, dim1, dim2, dim3, init_value) {}

// Destructor
template <typename T>
GaugeField<T>::~GaugeField() {}

// Get link
template <typename T>
SU_3<T> GaugeField<T>::get_link(size_t i0, size_t i1, size_t i2, size_t i3, size_t mu) const {
    return (*this)(i0, i1, i2, i3)[mu];
}

// Get rect
template <typename T>
std::complex<T> GaugeField<T>::get_rect(size_t i0, size_t i1, size_t i2, size_t i3) const {
    std::complex<T> result = 0.0;

    // This is performing the local plaquette: U_mu(x)U_nu(x+mu)U_mu^dagger(x+nu)U_nu^dagger(x)
    // x + mu sums +1 to the mu-th index, and x + nu sums +1 to the nu-th index.

    // In order: (mu, nu) = (0, 1), (0, 2), (0, 3), (1, 2), (1, 3), (2, 3)
    result = (get_link(i0, i1   , i2, i3, 0)           * get_link(i0 +1, i1, i2, i3, 1) \
            * get_link(i0, i1 +1, i2, i3, 0).adjoint() * get_link(i0   , i1, i2, i3, 1).adjoint()).trace();

    result += (get_link(i0, i1, i2, i3, 0)             * get_link(i0 +1, i1, i2, i3, 2) \
             * get_link(i0, i1, i2 +1, i3, 0).adjoint() * get_link(i0, i1, i2, i3, 2).adjoint()).trace();

    result += (get_link(i0, i1, i2, i3, 0)             * get_link(i0 +1, i1, i2, i3, 3) \
             * get_link(i0, i1, i2, i3 +1, 0).adjoint() * get_link(i0, i1, i2, i3, 3).adjoint()).trace();

    result += (get_link(i0, i1, i2, i3, 1)             * get_link(i0, i1 +1, i2, i3, 2) \
             * get_link(i0, i1, i2 +1, i3, 1).adjoint() * get_link(i0, i1, i2, i3, 2).adjoint()).trace();

    result += (get_link(i0, i1, i2, i3, 1)             * get_link(i0, i1 +1, i2, i3, 3) \
             * get_link(i0, i1, i2, i3 +1, 1).adjoint() * get_link(i0, i1, i2, i3, 3).adjoint()).trace();

    result += (get_link(i0, i1, i2, i3, 2)             * get_link(i0, i1, i2 +1, i3, 3) \
             * get_link(i0, i1, i2, i3 +1, 2).adjoint() * get_link(i0, i1, i2, i3, 3).adjoint()).trace();

    return result;
}


// Get plaquette
template <typename T>
std::complex<T> GaugeField<T>::get_plaquette() const {
    std::complex<T> result = 0.0;

    for (size_t i0 = 0; i0 < this->dim0; ++i0) {
        for (size_t i1 = 0; i1 < this->dim1; ++i1) {
            for (size_t i2 = 0; i2 < this->dim2; ++i2) {
                for (size_t i3 = 0; i3 < this->dim3; ++i3) {
                    result += get_rect(i0, i1, i2, i3);
                }
            }
        }
    }

    return result * (static_cast<T>(1.0) / (this->volume * 6));
}


// Randomize
template <typename T>
void GaugeField<T>::randomize() {

    // Randomize the field_values, FIXME: this currently puts float values from ranlux directly into
    // the SU_3 matrices. This is already not correct, as the SU_3 matrices should be unitary.

    auto gen = []() -> T { return 0.0; }; // Default lambda to avoid uninitialized use

    if constexpr (std::is_same<T, float>::value) {
        // Use Ranlxs
        Ranlxs<> gen(1234);
        // gen = [&ranluxs_gen]() -> double { return ranluxs_gen(); };
    } else if constexpr (std::is_same<T, double>::value) {
        // Use Ranlxd
        Ranlxd<> gen(1234);
        // gen = [&ranluxd_gen]() -> double { return ranluxd_gen(); };
    } else {
        static_assert(false, "Unsupported type for GaugeField");
    }

    for (auto elem : this->field_values) {
        for (SU_3<T>& su3 : elem) {
            for (size_t i = 0; i < 9; ++i) {
                su3.data[i] = gen();
            }
        }
    }
}

// Explicit template instantiations
template class SU_3<float>;
template class SU_3<double>;
template class GaugeField<float>;
template class GaugeField<double>;
