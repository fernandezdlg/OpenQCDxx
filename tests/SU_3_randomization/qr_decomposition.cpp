#include <Eigen/Dense>
#include <iostream>
#include <random>
#include "../../include/random/ranlxd.h"

int main() {
    std::cout << "QR decomposition of a random matrix" << "\n";

    Eigen::Matrix3cd A = {};

    // Generate a random matrix A with custom RNG and dist
    std::random_device rd;
    // Ranlxd<> engine(rd()); // FIXME: this is missing some member functions
    std::ranlux48 engine2(rd());
    std::normal_distribution<double> dist(0.0, 1.0);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            A(i, j) = std::complex<double>(dist(engine2), dist(engine2));
        }
    }

    // Print the matrix A
    std::cout << "Random (Ginibre) Matrix A:" << "\n" << A << "\n";

    // QR decomposition
    Eigen::HouseholderQR<Eigen::Matrix3cd> qr(A);
    Eigen::Matrix3cd Q = qr.householderQ();

    // Print the matrix Q (U(3) matrix)
    std::cout << "U(3) matrix Q:" << "\n" << Q << "\n";

    // Make it SU(3) matrix
    Eigen::Matrix3cd I = Eigen::Matrix3cd::Identity();
    std::cout << "Determinant is " << Q.determinant() << "\n";
    if (Q.determinant().real() < 0) {
        Q.col(0) = conj(Q.determinant()) * Q.col(0); // phase the first column TODO: is this the correct approach?
    }
    std::cout << "After normalizing: Matrix det(Q) is " << Q.determinant() << "\n";

    // Print the matrix Q (SU(3) matrix)
    std::cout << "SU(3) matrix Q:" << "\n" << Q << "\n";

}

