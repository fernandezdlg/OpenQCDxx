#include "lattice/LatticeField.h"
#include "common_utilities.h"
#include <random>


// Note: the typename T would be:
// For gauge fields: a length 4 / 8 array of SU(3) matrices (either with the fundamental
//  or adjoint representation, this would be abstracted in the operators implementation).
// For fermion fields: a length 4 array of complex numbers (a Dirac Spinor in each site).

// Constructor implementation.
template <typename T>
LatticeField<T>::LatticeField(
        const int dim0, const int dim1, const int dim2, const int dim3,
        const T default_value
    ) : dim0(dim0), dim1(dim1), dim2(dim2), dim3(dim3), volume(dim0, dim1 * dim2 * dim3) {
        // Initialize field_values to default_value FIXME: This is a bit ugly.
        if default_value != 0 {
            for (auto& sub_arr_3d : field_values) {
                for (auto& sub_arr_2d : sub_arr_3d) {
                    for (auto& sub_arr_1d : sub_arr_2d) {
                        sub_arr_1d.fill(default_value);
                    }
                }
            }
        }
    }


// Implementation of the print method.
template <typename T>
void LatticeField<T>::print(size_t i0, size_t i1, size_t i2, size_t i3) const {
    std::cout << "field_values[" << i0 << "][" << i1 << "][" << i2 << "][" << i3 << "] = "
              << field_values[i0][i1][i2][i3] << std::endl;
}


// Implementation of the randomize method.
template <typename T>
void LatticeField<T>::randomize() {
    std::random_device rd;
    std::mt19937 gen(rd());

    if constexpr (std::is_integral<T>::value) {
        std::uniform_int_distribution<T> dis(0, 100); // Adjust range as needed
        for (auto& sub_arr_3d : field_values) {
            for (auto& sub_arr_2d : sub_arr_3d) {
                for (auto& sub_arr_1d : sub_arr_2d) {
                    for (auto& elem : sub_arr_1d) {
                        elem = dis(gen);
                    }
                }
            }
        }

    } else if constexpr (std::is_floating_point<T>::value) {
        std::uniform_real_distribution<T> dis(0.0, 1.0); // Adjust range as needed
        for (auto& sub_arr_3d : field_values) {
            for (auto& sub_arr_2d : sub_arr_3d) {
                for (auto& sub_arr_1d : sub_arr_2d) {
                    for (auto& elem : sub_arr_1d) {
                        elem = dis(gen);
                    }
                }
            }
        }

    } else if constexpr (std::is_same<T, std::complex<float>>::value || std::is_same<T, std::complex<double>>::value) {
        std::uniform_real_distribution<typename T::value_type> dis(0.0, 1.0); // Adjust range as needed
        for (auto& sub_arr_3d : field_values) {
            for (auto& sub_arr_2d : sub_arr_3d) {
                for (auto& sub_arr_1d : sub_arr_2d) {
                    for (auto& elem : sub_arr_1d) {
                        elem = T(dis(gen), dis(gen));
                    }
                }
            }
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
