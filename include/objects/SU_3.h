#ifndef SU_3_H
#define SU_3_H

#include <complex>
#include <iostream>
#include <array>
#include "random/ranlxs.h"
#include "random/ranlxd.h"



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
        os << "[ \n";
        for (size_t i = 0; i < 3; ++i) {
            os << " [";
            for (size_t j = 0; j < 3; ++j) {
                os << su3_mat(i, j);
                if (j < 2) {
                    os << ", ";
                }
            }
            os << "] \n";
            if (i < 2) {
                os << ", ";
            }
        }
        os << "] \n";
        return os;
    }

    // Print the matrix TODO: check
    void print() const {
        std::cout << *this;
    }

    // Randomization according to the Haar measure.
    // Simple method for it is via the QR decomposition of a complex random matrix ∈ the Ginibre
    // ensemble. This matrix is then normalized to have determinant 1.
    void randomize(int seed = 0) const {

        // Generate a random matrix
        std::array<std::complex<T>, 9> random_matrix;
        // Gaussian distribution object
        std::normal_distribution<T> distribution(0, 1);

        if constexpr (std::is_same_v<T, float>) {
            generator = Ranlxs<>(seed);
            for (size_t i = 0; i < 9; ++i) {
                random_matrix[i] = std::complex<T>(distribution(generator), distribution(generator));
            }
        } else if constexpr (std::is_same_v<T, double>) {
            generator = Ranlxd<>(seed);
            for (size_t i = 0; i < 9; ++i) {
                random_matrix[i] = std::complex<T>(distribution(generator), distribution(generator));
            }
        }

        // Define the Householder vector function
        auto houseV = [](const std::vector<std::complex<T>>& x, // (chi1, x2...)
                               std::vector<std::complex<T>>& u, // (rho, u2...)
                               std::complex<T>& tau) {
            auto m = x.size();

            T chi2 = 0; // ||x[2:m]||_2
            for (auto it = x.begin() + 1; it != x.end(); ++it) {
                chi2 += std::norm(*it);
            }
            chi2 = std::sqrt(chi2);

            T alpha = std::abs( std::vector<T>{x[0],chi2} ); // = ||x||_2

            u[0] = alpha * x[0]/std::abs(x[0]);
            // u[0] = rho;

            std::complex<T> nu1 = x[0] - u[0];

            for (size_t i = 1; i < m; ++i) {
                u[i] = x[i]/nu1;
            }

            chi2 /= std::abs(nu1); // = ||u[2:m]||_2

            tau = (1 + chi2*chi2)/2;
        };


        // Perform the QR decomposition via Householder reflections (this is more robust than Gram-Schmidt)
        n = random_matrix.size();
        for (size_t j = 0; j < n; ++j) {
            std::vector<std::complex<T>> x(n-j);
            std::vector<std::complex<T>> u(n-j);
            std::complex<T> tau;

            for (size_t i = j; i < n; ++i) {
                x[i-j] = random_matrix[i*n + j];
            }

            houseV(x, u, tau);

            // Return x values to random_matrix
            for (size_t i = j; i < n; ++i) {
                random_matrix[i*n + j] = x[i-j];
            }

            // Apply the Householder reflection to the remaining columns
            for (size_t k = j; k < n; ++k) {
                std::complex<T> dot = 0;
                for (size_t i = j; i < n; ++i) {
                    dot += std::conj(u[i-j]) * random_matrix[i*n + k];
                }
                for (size_t i = j; i < n; ++i) {
                    random_matrix[i*n + k] -= tau * u[i-j] * dot;
                }
            }

            // Save the u values on random_matrix
            for (size_t i = j+1; i < n; ++i) {
                random_matrix[i*n + j] = u[i-j];
            }
        }

        // Accumulate the Q matrix
        std::array<std::complex<T>, 9> Q; // Q will U(3). Then normalize it to det(Q) = 1.
        // Initialize Q to the identity matrix
        for (size_t i = 0; i < 3; ++i) {
            Q[4*i] = 0;
        }

        for (size_t j = n-1; j >= 0; --j) {
            std::vector<std::complex<T>> v(n-j + 1);
            v[0] = 1;
            for (size_t i = j+1; i < n; ++i) {
                v[i-j] = random_matrix[i*n + j];
            }

            T norm_sub_A = 0;
            for (size_t i = 0; i < n-j; ++i) {
                norm_sub_A += std::norm(v[i]);
            }

            std::complex<T> beta = 2/(1 + norm_sub_A);

            for (size_t i = j; i < n; ++i) {
                std::complex<T> dot = 0;
                for (size_t k = j; k < n; ++k) {
                    dot += std::conj(v[k-j]) * Q[k*n + i];
                }
                for (size_t k = j; k < n; ++k) {
                    Q[k*n + i] -= beta * v[k-j] * dot;
                }
            }

        }

        // Normalize the determinant
        std::complex<T> det = 1;
        for (size_t i = 0; i < 3; ++i) {
            det *= Q[4*i];
        }

        if (det.real() < 0) {
            for (size_t i = 0; i < 9; ++i) {
                Q[i] = -Q[i];
            }
        }

        // Assign the matrix to the SU_3 data
        data = Q;

    }

    // Alternatively, we can generate a random matrix with the following properties:
    // 1. The diagonal elements are uniformly distributed in the interval [0, 2π].
    // 2. The off-diagonal elements are uniformly distributed in the interval [0, 2π].
    // 3. The matrix is normalized to have determinant 1.
    // This method is not as efficient as the QR decomposition method, but it is simple to implement.



private:
    std::array<std::complex<T>, 9> data;
};

#endif // SU_3_H
