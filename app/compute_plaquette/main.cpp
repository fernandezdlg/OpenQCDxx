#include <vector>
#include <iostream>
#include "gauge/GaugeField.h"

// FIXME: this is not the intended use case.
int main() {
    GaugeField gaugeField;
    std::vector<double> stencil = {1.0, 2.0, 3.0, 4.0}; // Example stencil values
    double plaquette = gaugeField.compute_plaquette(stencil);
    std::cout << "Plaquette: " << plaquette << std::endl;
    return 0;
}
