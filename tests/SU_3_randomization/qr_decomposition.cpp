#include <Eigen/Dense>
#include <iostream>
#include <random>
// #include "../../include/random/ranlxd.h"

int main() {
    size_t rows, cols;
    rows = 5;
    cols = 8;

    std::cout << "QR decomposition of a random matrix" << "\n";

    Eigen::MatrixXcd A(rows, cols);

    // Generate a random matrix A with custom RNG and dist
    std::random_device rd;
    std::ranlux48 engine2(rd());
    std::normal_distribution<double> dist(0.0, 1.0);

    for (int i = 0; i < A.rows(); i++) {
        for (int j = 0; j < A.cols(); j++) {
            A(i, j) = std::complex<double>(dist(engine2), dist(engine2));
        }
    }

    // Print the matrix A
    std::cout << "Random (Ginibre) Matrix A:" << "\n" << A << "\n";

    // QR decomposition
    Eigen::HouseholderQR<Eigen::MatrixXcd> qr(A);
    Eigen::MatrixXcd Q = qr.householderQ();
    Eigen::MatrixXcd R = qr.matrixQR().triangularView<Eigen::Upper>();

    // Print the matrix Q and R
    std::cout << "matrix Q:" << "\n" << Q << "\n";
    std::cout << "matrix R:" << "\n" << R << "\n";

    // Print Q*R
    std::cout << "Q*R:" << "\n" << Q*R << "\n";

}

