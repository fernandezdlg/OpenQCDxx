#ifndef GAUGEFIELD_H
#define GAUGEFIELD_H

#include <complex>
#include <iostream>
#include <array>
#include "include/random/ranlxs.h"
#include "include/random/ranlxd.h"



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

    // Accessor
    std::complex<T>& operator()(size_t row, size_t col) {
        return data[row * 3 + col];
    }

    const std::complex<T>& operator()(size_t row, size_t col) const {
        return data[row * 3 + col];
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

    // U * V operations
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

    // Print the matrix
    void print() const {
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
private: // FIXME:?
    std::array<std::complex<T>, 9> data;
};


// TODO: Define the SU(3) class via the adjoint representation? This would require changing names.


// Define the GaugeField class
template <typename T>
class GaugeField {
public:
    GaugeField(size_t dim0, size_t dim1, size_t dim2, size_t dim3) :
        dim0(dim0), dim1(dim1), dim2(dim2), dim3(dim3), volume(dim0 * dim1 * dim2 * dim3) {
        field_data.resize(volume, {std::array<SU_3<T>, 4>()});
        }
    GaugeField(size_t dim0, size_t dim1, size_t dim2, size_t dim3, SU_3<T> init_value) :
        dim0(dim0), dim1(dim1), dim2(dim2), dim3(dim3), volume(dim0 * dim1 * dim2 * dim3) {
        field_data.resize(volume, {std::array<SU_3<T>, 4>(init_value)});
        }
    ~GaugeField() {}


    SU_3<T> get_link(size_t i0, size_t i1, size_t i2, size_t i3, size_t mu) const {
        return field_data[i0 * dim1 * dim2 * dim3 + i1 * dim2 * dim3 + i2 * dim3 + i3][mu];
    }

    std::complex<T> get_rect(size_t i0, size_t i1, size_t i2, size_t i3) const {
        std::complex<T> result = 0.0;

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

    std::complex<T> get_plaquette() const {
        std::complex<T> result = 0.0;
        for (size_t i0 = 0; i0 < dim0; ++i0) {
            for (size_t i1 = 0; i1 < dim1; ++i1) {
                for (size_t i2 = 0; i2 < dim2; ++i2) {
                    for (size_t i3 = 0; i3 < dim3; ++i3) {
                        result += get_rect(i0, i1, i2, i3);
                    }
                }
            }
        }
        return result * static_cast<T>(1.0 / (6 * volume));
    }

    // TODO:
    // std::complex<T> get_spatial_plaquette() const;
    // std::complex<T> get_temporal_plaquette() const;
    // std::complex<T> get_wilson_loop(...) const;

    void randomize() {
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

        for (auto elem : field_data) {
            for (SU_3<T>& su3 : elem) {
                for (size_t i = 0; i < 3; ++i) {
                    for (size_t j = 0; j < 3; ++j) {
                        su3(i,j) = gen();
                    }
                }
            }
        }
    }

    void set_link(size_t i0, size_t i1, size_t i2, size_t i3, size_t mu, const SU_3<T>& link) {
        field_data[i0 * dim1 * dim2 * dim3 + i1 * dim2 * dim3 + i2 * dim3 + i3][mu] = link;
    }
private:
    const size_t dim0, dim1, dim2, dim3;
    const size_t volume;
    std::vector<std::array<SU_3<T>, 4>> field_data;
};

#endif // GAUGEFIELD_H
