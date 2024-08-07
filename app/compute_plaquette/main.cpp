#include <vector>
#include <iostream>
#include "gauge/GaugeField.h"

int main() {
    // Init Gauge Field on the stack.
    GaugeField gaugeField(4, 4, 4, 4, default_value = 0.0);

    // 
    GaugeField.randomize();
    double plaquette = gaugeField.compute_plaquette();
    std::cout << "Plaquette: " << plaquette << std::endl;
    return 0;
}
