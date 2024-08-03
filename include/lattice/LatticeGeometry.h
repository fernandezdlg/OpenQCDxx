#ifndef LATTICEGEOMETRY_H
#define LATTICEGEOMETRY_H

#include <complex>
#include <iostream>
#include <vector>

template <typename T>
class LatticeGeometry {
public:
    LatticeGeometry(int dim1, int dim2, int dim3, int dim4);
    ~LatticeGeometry() = default;

    void initialize();
    void print() const;
    void randomize();

private:
    int dim1, dim2, dim3, dim4;
    std::vector<T> stencil;

    int index(int i, int j, int k, int l) const;
};

#endif // LATTICEGEOMETRY_H
