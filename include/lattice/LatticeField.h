#ifndef LATTICEFIELD_H
#define LATTICEFIELD_H

#include <complex>
#include <iostream>
#include <vector>
#include <array>
#include <functional>

// TODO: For Gauge and Spinor field implementation, add an extra parameter of the representation.
// I.e. this LatticeField is a container for the field values, of type T.
// The container for Gauge fields would be a container of SU(N) matrices (templated type M), and
// each matrix entry of type T (e.g., a std::complex<double>). Additionally, it will have an extra
// set of internal indices for the dirac and color indices.
template <typename T>
class LatticeField {
public:
    LatticeField(
        const size_t dim0, const size_t dim1, const size_t dim2, const size_t dim3,
        const T init_value
    );
    ~LatticeField() = default;

    T& operator()(size_t i0, size_t i1, size_t i2, size_t i3);
    const T& operator()(size_t i0, size_t i1, size_t i2, size_t i3) const;
    size_t get_flat_idx(size_t i0, size_t i1, size_t i2, size_t i3) const;

    void randomize();  // TODO: add options to randomize with different distributions
    void randomize_sequential();  // Example of a serial implementation.

    // This will do a parallel application of fun on each element in field_values.
    void func(std::function<void(T&)> fun);
    void func_sequential(std::function<void(T&)> fun);

    // This will perform a binary operator between all values in field_values after filtering by a
    // logic predicate.
    T reduce_if(std::function<bool(const T&)> predicate, T init, std::function<T(const T&, const T&)> binary_op);
    T reduce_if_sequential(std::function<bool(const T&)> predicate, T init, std::function<T(const T&, const T&)> binary_op);


private:
    const size_t dim0, dim1, dim2, dim3;
    const size_t volume;
    // Maybe in the future we can use a mdvector / mdarray if something like that gets into the std.
    std::vector<T> field_values;
};

#endif // LATTICEFIELD_H
