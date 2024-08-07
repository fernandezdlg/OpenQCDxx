#include "lattice/LatticeField.h"
#include "common_utilities.h"
#include <random>


// Note: the typename T would be:
// For gauge fields: a length 4 / 8 array of SU(3) matrices (either with the fundamental
//  or adjoint representation, this would be abstracted in the operators implementation).
// For fermion fields: a length 4 array of complex numbers (a Dirac Spinor in each site).
template <typename T>
LatticeField<T>::LatticeField(
    const int dim1, const int dim2, const int dim3, const int dim4,
    const T& default_value
    ) : dim1(dim1), dim2(dim2), dim3(dim3), dim4(dim4),
        volume(dim1 * dim2 * dim3 * dim4),
        field_values(volume, default_value) {}

template <typename T>
int LatticeField<T>::index(int i, int j, int k, int l) const {
    return ((i * dim2 + j) * dim3 + k) * dim4 + l;
}

// This is super ugly, TODO: change this into using Eigen::Unsupported::Tensor, there might be a
// tiny inconvenience when trying to use C++ parallel STL in certain places, (i.e. when Eigen
// doesn't want to support non-CUDA GPUs)
template <typename T>
void LatticeField<T>::initialize() {
    for (int i = 0; i < dim1; ++i) {
        for (int j = 0; j < dim2; ++j) {
            for (int k = 0; k < dim3; ++k) {
                for (int l = 0; l < dim4; ++l) {
                    field_values[index(i, j, k, l)] = static_cast<T>(i + j + k + l);
                }
            }
        }
    }
}

template <typename T>
void LatticeField<T>::print() const {
    for (int i = 0; i < dim1; ++i) {
        for (int j = 0; j < dim2; ++j) {
            for (int k = 0; k < dim3; ++k) {
                for (int l = 0; l < dim4; ++l) {
                    std::cout << "field_values[" << i << "][" << j << "][" << k << "][" << l << "] = "
                              << field_values[index(i, j, k, l)] << std::endl;
                }
            }
        }
    }
}


template <typename T>
void LatticeField<T>::randomize() {
    std::random_device rd;
    std::mt19937 gen(rd());

    if constexpr (std::is_integral<T>::value) {
        std::uniform_int_distribution<T> dis(0, 100); // Adjust range as needed
        for (auto& elem : field_values) {
            elem = dis(gen);
        }
    } else if constexpr (std::is_floating_point<T>::value) {
        std::uniform_real_distribution<T> dis(0.0, 1.0); // Adjust range as needed
        for (auto& elem : field_values) {
            elem = dis(gen);
        }
    } else if constexpr (std::is_same<T, std::complex<float>>::value || std::is_same<T, std::complex<double>>::value) {
        std::uniform_real_distribution<typename T::value_type> dis(0.0, 1.0); // Adjust range as needed
        for (auto& elem : field_values) {
            elem = T(dis(gen), dis(gen));
        }
    } else {
        static_assert(always_false<T>::value, "Unsupported type");
    }
}


// Explicit template instantiations
template class LatticeField<float>;
template class LatticeField<double>;
template class LatticeField<std::complex<float>>;
template class LatticeField<std::complex<double>>;
