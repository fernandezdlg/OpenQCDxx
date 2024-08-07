#ifndef GAUGEFIELD_H
#define GAUGEFIELD_H

#include "lattice/LatticeField.h" // Include the header for LatticeField

// Define the subclass GaugeField
template <typename T>
class GaugeField : public LatticeField<T> {
public:
    GaugeField(int dim1, int dim2, int dim3, int dim4, const T& default_value)
        : LatticeField<T>(dim1, dim2, dim3, dim4, default_value) {};
    ~GaugeField() = default;

    // Additional methods specific to GaugeField can be added here
    T compute_plaquette() const;
};
