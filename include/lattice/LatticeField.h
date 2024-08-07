#ifndef LATTICEFIELD_H
#define LATTICEFIELD_H

#include <complex>
#include <iostream>
#include <vector>
#include "mdarray/mdarray.h"

template <typename T>
class LatticeField {
public:
    LatticeField(
        const int dim0, const int dim1, const int dim2, const int dim3,
        const T default_value
    );
    ~LatticeField() = default;

    void print(size_t i0, size_t i1, size_t i2, size_t i3) const;
    void randomize();

private:
    const int dim0, dim1, dim2, dim3;
    const int volume;
    std::array<T, volume> field_values;
};

#endif // LATTICEFIELD_H
