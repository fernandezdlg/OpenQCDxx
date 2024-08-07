#ifndef LATTICEGEOMETRY_H
#define LATTICEGEOMETRY_H

#include <complex>
#include <iostream>
#include <vector>

template <typename T>
class LatticeField {
public:
    LatticeField(
        const int dim1, const int dim2, const int dim3, const int dim4,
        const T& default_value
    );
    ~LatticeField() = default;

    void initialize();
    void print() const;
    void randomize();

private:
    int dim1, dim2, dim3, dim4;
    int volume;
    // TODO: values might be better as an Eigen Tensor? Check conflicts when using it with C++
    // parallel STL. Maybe ignore this and use an MDspan for connecting to algorithms.
    // FIXME: This is a bad idea, use std::vector instead.
    std::array<T> field_values;

    int index(int i, int j, int k, int l) const;
};

#endif // LATTICEGEOMETRY_H
