#include "lattice/LatticeGeometry.h"
#include <complex>

int main() {
    LatticeGeometry<float> latticeFloat(4, 4, 4, 4);
    latticeFloat.initialize();
    latticeFloat.print();

    LatticeGeometry<double> latticeDouble(4, 4, 4, 4);
    latticeDouble.initialize();
    latticeDouble.print();

    LatticeGeometry<std::complex<float>> latticeComplexFloat(4, 4, 4, 4);
    latticeComplexFloat.initialize();
    latticeComplexFloat.print();

    LatticeGeometry<std::complex<double>> latticeComplexDouble(4, 4, 4, 4);
    latticeComplexDouble.initialize();
    latticeComplexDouble.print();

    return 0;
}