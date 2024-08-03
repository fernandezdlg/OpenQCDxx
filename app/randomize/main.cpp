#include "lattice/LatticeGeometry.h"
#include <complex>

int main() {
    LatticeGeometry<float> latticeFloat(4, 4, 4, 4);
    latticeFloat.initialize();
    latticeFloat.randomize();

    latticeFloat.print();


    LatticeGeometry<std::complex<float>> latticeComplexFloat(4, 4, 4, 4);
    latticeComplexFloat.initialize();
    latticeComplexFloat.randomize();
    latticeComplexFloat.print();



    return 0;
}