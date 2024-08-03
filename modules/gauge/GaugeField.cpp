#include "lattice/LatticeGeometry.h" // Include the header for LatticeGeometry
#include "gauge/GaugeField.h"
#include <numeric>           // For std::accumulate
#include <vector>            // For std::vector

// Define the subclass GaugeField
class GaugeField : public LatticeGeometry {
public:
    // Constructor
    GaugeField() : LatticeGeometry() {}

    // Function to compute the plaquette
    double compute_plaquette(const std::vector<double>& stencil) {
        // Perform a reduction sum over all the values in the stencil
        return std::accumulate(stencil.begin(), stencil.end(), 0.0);
    }
};

