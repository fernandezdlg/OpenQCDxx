#include <Eigen/Dense>
#include <iostream>
#include <random>


int main() {
    size_t N;
    N = 3;

    std::cout << "SU(N) random matrix" << "\n";

    Eigen::MatrixXcd A(N, N);

    // Generate a random matrix A with custom RNG and dist
    // std::random_device rd;
    std::ranlux48 engine2(0);
    std::normal_distribution<double> dist(0.0, 1.0);

    for (int i = 0; i < A.rows(); i++) {
        for (int j = 0; j < A.cols(); j++) {
            A(i, j) = std::complex<double>(dist(engine2), dist(engine2));
        }
    }

    // Print the matrix A
    std::cout << "Random (Ginibre) Matrix A:" << "\n" << A << "\n\n";

    // QR decomposition
    Eigen::HouseholderQR<Eigen::MatrixXcd> qr(A);
    Eigen::MatrixXcd Q = qr.householderQ();

    // Print the matrix Q and R
    std::cout << "matrix Q ∈ U(N):" << "\n" << Q << "\n\n";
    std::cout << "matrix Q^t:" << "\n" << Q.adjoint() << "\n\n";

    // Print Q^t * Q
    std::cout << "Q^t*Q:" << "\n" << Q.adjoint()*Q << "\n\n";

    // Get the determinant of Q
    std::cout << "Determinant of Q: " << Q.determinant() << "\n";

    // Divide Q by the determinant^(1/N)
    Q /= std::pow(Q.determinant(), 1.0/N);

    // Print the matrix Q (SU(N) matrix)
    std::cout << "SU(N) matrix Q:" << "\n" << Q << "\n";

    // Print Q^t * Q
    std::cout << "Q^t*Q:" << "\n" << Q.adjoint()*Q << "\n\n";

    // Print the determinant of Q
    std::cout << "Determinant of Q: " << Q.determinant() << "\n";
}
