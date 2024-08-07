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
        const int dim1, const int dim2, const int dim3, const int dim4,
        const T default_value
    );
    ~LatticeField() = default;

    void print() const;
    void randomize();

private:
    int dim1, dim2, dim3, dim4;
    int volume;
    // FIXME: Better to use std::vector instead?
    mdarray<T, dim0, dim1, dim2, dim3> field_values;

};

#endif // LATTICEFIELD_H
