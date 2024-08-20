#include "lattice/GaugeField.h"
#include <iostream>


int main() {
    // Create a random gauge field
    GaugeField<double> gfield(2,2,2,2);
    gfield.randomize();

    // Print the gauge field
    std::cout << "Gauge field:" << "\n";
    std::cout << "-----------" << "\n";
    std::cout << "Link x = 0,0,0,0; mu = 0:" << "\n";
    gfield.get_link(0,0,0,0,0).print();

    return 0;
}
