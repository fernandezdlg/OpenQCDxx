#include "lattice/LatticeField.h"
#include <complex>

int main() {
    LatticeField<float> latticeFloat(4, 4, 4, 4);
    latticeFloat.initialize();
    latticeFloat.randomize();

    latticeFloat.print();


    LatticeField<std::complex<float>> latticeComplexFloat(4, 4, 4, 4);
    latticeComplexFloat.initialize();
    latticeComplexFloat.randomize();
    latticeComplexFloat.print();



    return 0;
}