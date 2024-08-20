#include "objects/SU_3.h"
#include <iostream>
#include <array>
#include <complex>


int main() {
    // Create a SU(3) matrix
    SU_3<double> su3_mat;
    std::cout << "Printing the SU_3 matrix with the default constructor" << "\n";
    su3_mat.print();

    // Create a SU(3) matrix from defined values
    SU_3<double> su3_mat_values({{{1.0,1.0}, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0}});
    std::cout << "Printing the SU_3 matrix with defined values" << "\n";
    su3_mat_values.print();

    // Create a copy of the SU(3) matrix
    SU_3<double> su3_mat_copy(su3_mat_values);
    std::cout << "Printing the original and the copy of SU_3" << "\n";
    su3_mat_values.print();
    su3_mat_copy.print();

    // Move the SU(3) matrix
    SU_3<double> su3_mat_move(std::move(su3_mat_copy));
    std::cout << "Printing the original and the moved SU_3" << "\n";
    su3_mat_copy.print();
    su3_mat_move.print();

    // Access the elements of the SU(3) matrix and modify a value
    std::cout << "Accessing the elements of the SU_3 matrix" << "\n";
    std::cout << "su3_mat_values(0,0) = " << su3_mat_values(0,0) << "\n";
    su3_mat_values(0,0) = 10.0;
    std::cout << "Modified value (0, 0) to 10.0" << "\n";
    std::cout << "su3_mat_values(0,0) = " << su3_mat_values(0,0) << "\n";

    // Testing stream operator
    std::cout << "Printing the SU_3 matrix using the stream operator" << "\n";
    std::cout << su3_mat_values << "\n";

    // Create U and V for SU_3 matrices, then test +, -, and * operations
    SU_3<double> U({std::array<std::complex<double>,9>{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0}});
    SU_3<double> V({std::array<std::complex<double>,9>{9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0}});
    std::cout << "Printing the SU_3 matrices U and V" << "\n";
    std::cout << " U =" << U << "\n";
    std::cout << " V =" << V << "\n";

    // Test U + V
    std::cout << "U + V" << "\n";
    std::cout << U + V << "\n";

    // Test U - V
    std::cout << "U - V" << "\n";
    std::cout << U - V << "\n";

    // Test U * V
    std::cout << "U * V" << "\n";
    std::cout << U * V << "\n";

    // Test W = {{{1.0, 1.0}, {1.0, 1.0}, {1.0, 1.0},
    //            {1.0, 1.0}, {1.0, 1.0}, {1.0, 1.0},
    //            {1.0, 1.0}, {1.0, 1.0}, {1.0, 1.0}}}
    SU_3<double> W({{{1.0, 1.0}, {2.0, 1.0}, {3.0, 1.0},
                     {4.0, 1.0}, {5.0, 1.0}, {6.0, 1.0},
                     {7.0, 1.0}, {8.0, 1.0}, {9.0, 1.0}}});
    std::cout << "Printing the SU_3 matrix W = " << W << "\n";
    std::cout << "Printing the dagger of W = " << W.adjoint() << "\n";
    std::cout << "Printing the trace of W = " << W.trace() << "\n";

    return 0;
}
