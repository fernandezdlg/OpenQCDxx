#include "lattice/LatticeField.h"
#include <complex>

int main() {
    LatticeField<float> latticeFloat(4, 4, 4, 4, 0.0);
    latticeFloat.print(1,2,2,3);

    LatticeField<double> latticeDouble(4, 4, 4, 4, 1.0);
    latticeFloat.print(1,2,2,3);

    LatticeField<std::complex<float>> latticeComplexFloat(4, 4, 4, 4, std::complex<float>(0.0, 0.0));
    latticeComplexFloat.print(0,0,0,0);
    latticeComplexFloat.print(0,0,3,0);

    LatticeField<std::complex<double>> latticeComplexDouble(4, 4, 4, 4, std::complex<double>(1.0, 1.0));
    latticeComplexDouble.print(0,0,0,0);
    latticeComplexDouble.print(0,0,3,0);

    return 0;
}
