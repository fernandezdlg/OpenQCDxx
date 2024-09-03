#include <Eigen/Dense>
#include <cstddef>
#include <random>
#include <fstream>
#include <iomanip>


int main() {
    size_t N, N_samples;
    N = 3;
    N_samples = 200000;

    // Generate N_samples U(N) random matrices, get their eigenvalues and produce a histogram with
    // their modulus and phase values. The eigenvalues are complex doubles.

    // Instantiate the RNG and the dist for the Ginibre generation step.
    std::ranlux48 engine(0);
    std::normal_distribution<double> dist(0.0, 1.0);

    // Containers for the eigenvalues
    std::vector<double> eigenvalues_modulus;
    std::vector<double> eigenvalues_phase;

    std::vector<double> eigenvalues_modulus2;
    std::vector<double> eigenvalues_phase2;

    // Instantiate the matrix A which will be reused for each sample.
    Eigen::MatrixXcd A(N, N);

    for (size_t i = 0; i < N_samples; ++i) {
        // Randomize matrix A with custom RNG and dist
        for (size_t i = 0; i < A.rows(); i++) {
            for (size_t j = 0; j < A.cols(); j++) {
                A(i, j) = std::complex<double>(dist(engine), dist(engine));
            }
        }

        // Get the Q matrix from the QR decomposition
        Eigen::HouseholderQR<Eigen::MatrixXcd> qr(A);
        Eigen::MatrixXcd Q = qr.householderQ();
        Eigen::MatrixXcd R = qr.matrixQR().triangularView<Eigen::Upper>();

        Eigen::MatrixXcd L(N, N);
        L.setZero();

        for (size_t i = 0; i < N; ++i) {
            L(i, i) = R(i, i) / std::abs(R(i, i));
        }

        auto Q2 = Q * L;

        // Get the eigenvalues of Q
        auto temp = Q.eigenvalues();
        auto temp2 = Q2.eigenvalues();

        // Store the eigenvalues in the containers
        for (size_t i = 0; i < temp.size(); ++i) {
            eigenvalues_modulus.push_back(std::abs(temp[i]));
            eigenvalues_phase.push_back(std::arg(temp[i]));
            eigenvalues_modulus2.push_back(std::abs(temp2[i]));
            eigenvalues_phase2.push_back(std::arg(temp2[i]));
        }
    }

    // Save the eigenvalues to a csv file with 12 decimal places
    std::ofstream file;
    file.open("eigenvalues_HH.csv");
    file << "modulus,phase\n";
    for (size_t i = 0; i < eigenvalues_modulus.size(); ++i) {
        file << std::fixed << std::setprecision(12) << eigenvalues_modulus[i] << "," << eigenvalues_phase[i] << "\n";
    }
    file.close();

    file.open("eigenvalues_HH_corr.csv");
    file << "modulus,phase\n";
    for (size_t i = 0; i < eigenvalues_modulus2.size(); ++i) {
        file << std::fixed << std::setprecision(12) << eigenvalues_modulus2[i] << "," << eigenvalues_phase2[i] << "\n";
    }
    file.close();

    // Reset the containers
    eigenvalues_modulus.clear();
    eigenvalues_phase.clear();
    eigenvalues_modulus2.clear();
    eigenvalues_phase2.clear();


    for (size_t i = 0; i < N_samples; ++i) {
        // Randomize matrix A with custom RNG and dist
        for (size_t i = 0; i < A.rows(); i++) {
            for (size_t j = 0; j < A.cols(); j++) {
                A(i, j) = std::complex<double>(dist(engine), dist(engine));
            }
        }

        // Get the Q matrix from the QR decomposition
        Eigen::ColPivHouseholderQR<Eigen::MatrixXcd> qr(A);
        Eigen::MatrixXcd Q = qr.matrixQ();
        Eigen::MatrixXcd R = qr.matrixQR().triangularView<Eigen::Upper>();

        // gauge setting with R
        Eigen::MatrixXcd L(N, N);
        L.setZero();

        for (size_t i = 0; i < N; ++i) {
            L(i, i) = R(i, i) / std::abs(R(i, i));
        }

        auto Q2 = Q * L;

        // Get the eigenvalues of Q
        auto temp = Q.eigenvalues();
        auto temp2 = Q2.eigenvalues();

        // Store the eigenvalues in the containers
        for (size_t i = 0; i < temp.size(); ++i) {
            eigenvalues_modulus.push_back(std::abs(temp[i]));
            eigenvalues_phase.push_back(std::arg(temp[i]));
            eigenvalues_modulus2.push_back(std::abs(temp2[i]));
            eigenvalues_phase2.push_back(std::arg(temp2[i]));
        }
    }

    // Save the eigenvalues to a csv file with 12 decimal places
    file.open("eigenvalues_colpiv.csv");
    file << "modulus,phase\n";
    for (size_t i = 0; i < eigenvalues_modulus.size(); ++i) {
        file << std::fixed << std::setprecision(12) << eigenvalues_modulus[i] << "," << eigenvalues_phase[i] << "\n";
    }
    file.close();

    file.open("eigenvalues_colpiv_corr.csv");
    file << "modulus,phase\n";
    for (size_t i = 0; i < eigenvalues_modulus2.size(); ++i) {
        file << std::fixed << std::setprecision(12) << eigenvalues_modulus2[i] << "," << eigenvalues_phase2[i] << "\n";
    }
    file.close();

    // Reset the containers
    eigenvalues_modulus.clear();
    eigenvalues_phase.clear();
    eigenvalues_modulus2.clear();
    eigenvalues_phase2.clear();


    for (size_t i = 0; i < N_samples; ++i) {
        // Randomize matrix A with custom RNG and dist
        for (size_t i = 0; i < A.rows(); i++) {
            for (size_t j = 0; j < A.cols(); j++) {
                A(i, j) = std::complex<double>(dist(engine), dist(engine));
            }
        }

        // Get the Q matrix from the QR decomposition
        Eigen::FullPivHouseholderQR<Eigen::MatrixXcd> qr(A);
        Eigen::MatrixXcd Q = qr.matrixQ();
        Eigen::MatrixXcd R = qr.matrixQR().triangularView<Eigen::Upper>();

        // gauge setting with R
        Eigen::MatrixXcd L(N, N);
        L.setZero();

        for (size_t i = 0; i < N; ++i) {
            L(i, i) = R(i, i) / std::abs(R(i, i));
        }

        auto Q2 = Q * L;

        // Get the eigenvalues of Q
        auto temp = Q.eigenvalues();
        auto temp2 = Q2.eigenvalues();

        // Store the eigenvalues in the containers
        for (size_t i = 0; i < temp.size(); ++i) {
            eigenvalues_modulus.push_back(std::abs(temp[i]));
            eigenvalues_phase.push_back(std::arg(temp[i]));
            eigenvalues_modulus2.push_back(std::abs(temp2[i]));
            eigenvalues_phase2.push_back(std::arg(temp2[i]));
        }
    }

    // Save the eigenvalues to a csv file with 12 decimal places
    file.open("eigenvalues_fullpiv.csv");
    file << "modulus,phase\n";
    for (size_t i = 0; i < eigenvalues_modulus.size(); ++i) {
        file << std::fixed << std::setprecision(12) << eigenvalues_modulus[i] << "," << eigenvalues_phase[i] << "\n";
    }
    file.close();

    // Save the eigenvalues to a csv file with 12 decimal places
    file.open("eigenvalues_fullpiv_corr.csv");
    file << "modulus,phase\n";
    for (size_t i = 0; i < eigenvalues_modulus2.size(); ++i) {
        file << std::fixed << std::setprecision(12) << eigenvalues_modulus2[i] << "," << eigenvalues_phase2[i] << "\n";
    }
    file.close();

    // Reset the containers
    eigenvalues_modulus.clear();
    eigenvalues_phase.clear();
    eigenvalues_modulus2.clear();
    eigenvalues_phase2.clear();


    return 0;
}
