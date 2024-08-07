#ifndef GAUGEFIELD_H
#define GAUGEFIELD_H

#include "lattice/LatticeGeometry.h" // Include the header for LatticeGeometry
#include <vector>            // For std::vector

// Define the subclass GaugeField
class GaugeField : public LatticeGeometry {
public:
    // Constructor
    GaugeField();

    // Function to compute the plaquette
    double compute_plaquette(const std::vector<double>& stencil);
};

#endif // GAUGEFIELD_H
