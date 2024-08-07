#include "lattice/LatticeField.h" // Include the header for LatticeField
#include "gauge/GaugeField.h"
#include <numeric>           // For std::accumulate
#include <vector>            // For std::vector

// Define the subclass GaugeField
template <typename T>  // In here, T would be a length 4 / 8 array of SU(3) matrices.
class GaugeField : public LatticeField {
public:
    // Constructor
    GaugeField() : LatticeField() {}

    // Function to compute the plaquette
    double compute_plaquette(const std::vector<double>& field_values) const{
        // Perform a reduction sum over all the values in the field_values
        return std::accumulate(field_values.begin(), field_values.end(), 0.0);
    }
};



#include "GaugeField.h"

template <typename T>
GaugeField<T>::GaugeField(int dim1, int dim2, int dim3, int dim4)
    : LatticeField<T>(dim1, dim2, dim3, dim4) {
    // Additional initialization specific to GaugeField can be added here

}

// Explicit template instantiation
template class GaugeField<float>;
template class GaugeField<double>;
template class GaugeField<std::complex<float>>;
template class GaugeField<std::complex<double>>;