#include "lattice/LatticeGeometry.h"
#include "common_utilities.h"
#include <random>


template <typename T>
LatticeGeometry<T>::LatticeGeometry(int dim1, int dim2, int dim3, int dim4)
    : dim1(dim1), dim2(dim2), dim3(dim3), dim4(dim4), stencil(dim1 * dim2 * dim3 * dim4) {}

template <typename T>
int LatticeGeometry<T>::index(int i, int j, int k, int l) const {
    return ((i * dim2 + j) * dim3 + k) * dim4 + l;
}

template <typename T>
void LatticeGeometry<T>::initialize() {
    for (int i = 0; i < dim1; ++i) {
        for (int j = 0; j < dim2; ++j) {
            for (int k = 0; k < dim3; ++k) {
                for (int l = 0; l < dim4; ++l) {
                    stencil[index(i, j, k, l)] = static_cast<T>(i + j + k + l);
                }
            }
        }
    }
}

template <typename T>
void LatticeGeometry<T>::print() const {
    for (int i = 0; i < dim1; ++i) {
        for (int j = 0; j < dim2; ++j) {
            for (int k = 0; k < dim3; ++k) {
                for (int l = 0; l < dim4; ++l) {
                    std::cout << "stencil[" << i << "][" << j << "][" << k << "][" << l << "] = "
                              << stencil[index(i, j, k, l)] << std::endl;
                }
            }
        }
    }
}


template <typename T>
void LatticeGeometry<T>::randomize() {
    std::random_device rd;
    std::mt19937 gen(rd());

    if constexpr (std::is_integral<T>::value) {
        std::uniform_int_distribution<T> dis(0, 100); // Adjust range as needed
        for (auto& elem : stencil) {
            elem = dis(gen);
        }
    } else if constexpr (std::is_floating_point<T>::value) {
        std::uniform_real_distribution<T> dis(0.0, 1.0); // Adjust range as needed
        for (auto& elem : stencil) {
            elem = dis(gen);
        }
    } else if constexpr (std::is_same<T, std::complex<float>>::value || std::is_same<T, std::complex<double>>::value) {
        std::uniform_real_distribution<typename T::value_type> dis(0.0, 1.0); // Adjust range as needed
        for (auto& elem : stencil) {
            elem = T(dis(gen), dis(gen));
        }
    } else {
        static_assert(always_false<T>::value, "Unsupported type");
    }
}


// Explicit template instantiation
template class LatticeGeometry<float>;
template class LatticeGeometry<double>;
template class LatticeGeometry<std::complex<float>>;
template class LatticeGeometry<std::complex<double>>;
