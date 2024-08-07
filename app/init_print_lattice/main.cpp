#include "lattice/LatticeField.h"
#include <complex>

int main() {
    LatticeField<float> latticeFloat(4, 4, 4, 4);
    latticeFloat.initialize();
    latticeFloat.print();

    LatticeField<double> latticeDouble(4, 4, 4, 4);
    latticeDouble.initialize();
    latticeDouble.print();

    LatticeField<std::complex<float>> latticeComplexFloat(4, 4, 4, 4);
    latticeComplexFloat.initialize();
    latticeComplexFloat.print();

    LatticeField<std::complex<double>> latticeComplexDouble(4, 4, 4, 4);
    latticeComplexDouble.initialize();
    latticeComplexDouble.print();

    return 0;
}