#include "lattice/LatticeField.h"
#include <complex>
#include <iostream>

int main() {
    LatticeField<float> latticeFloat(4, 4, 4, 4, 0.0);
    std::cout << "latticeFloat(0,1,2,3) : " << latticeFloat(0,1,2,3) << std::endl;

    LatticeField<double> latticeDouble(4, 4, 4, 4, 1.0);
    std::cout << "latticeDouble(0,1,2,3) : " << latticeDouble(0,1,2,3) << std::endl;

    LatticeField<std::complex<float>> latticeComplexFloat(4, 4, 4, 4, std::complex<float>(0.0, 0.0));
    std::cout << "latticeComplexFloat(0,0,0,0) : " << latticeComplexFloat(0,0,0,0) << std::endl;
    std::cout << "latticeComplexFloat(0,1,2,3) : " << latticeComplexFloat(0,1,2,3) << std::endl;

    LatticeField<std::complex<double>> latticeComplexDouble(4, 4, 4, 4, std::complex<double>(1.0, 1.0));
    std::cout << "latticeComplexDouble(0,0,0,0) : " << latticeComplexDouble(0,0,0,0) << std::endl;
    std::cout << "latticeComplexDouble(0,1,2,3) : " << latticeComplexDouble(0,1,2,3) << std::endl;

    // Randomize the lattice complex double field
    std::cout << "Randomizing latticeComplexDouble..." << std::endl;
    latticeComplexDouble.randomize();
    std::cout << "latticeComplexDouble(0,0,0,0) : " << latticeComplexDouble(0,0,0,0) << std::endl;
    std::cout << "latticeComplexDouble(0,0,0,1) : " << latticeComplexDouble(0,0,0,1) << std::endl;
    std::cout << "latticeComplexDouble(0,0,0,2) : " << latticeComplexDouble(0,0,0,2) << std::endl;
    std::cout << "latticeComplexDouble(0,0,0,3) : " << latticeComplexDouble(0,0,0,3) << std::endl;
    std::cout << "latticeComplexDouble(0,0,0,4) : " << latticeComplexDouble(0,0,0,4) << std::endl;

    return 0;
}
