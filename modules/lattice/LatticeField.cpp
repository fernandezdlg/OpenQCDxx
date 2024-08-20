#include "lattice/LatticeField.h"
#include <random>
#include <algorithm>
#include <execution>
#include <numeric>


// Constructor implementations.
template <typename T>
LatticeField<T>::LatticeField(size_t dim0, size_t dim1, size_t dim2, size_t dim3)
    : dim0(dim0), dim1(dim1), dim2(dim2), dim3(dim3),
      volume(dim0 * dim1 * dim2 * dim3)
{
    field_values.resize(volume);
}



template <typename T>
LatticeField<T>::LatticeField(
        size_t dim0, size_t dim1, size_t dim2, size_t dim3,
        T init_value
) : dim0(dim0), dim1(dim1), dim2(dim2), dim3(dim3),
    volume(dim0 * dim1 * dim2 * dim3)
{
    field_values.resize(volume, init_value);
}


// Destructor implementation.
template <typename T>
LatticeField<T>::~LatticeField() {
    // For now, nothing to do here, the vector will be automatically destroyed. Maybe for later when
    // we instantiate in the heap: TODO:?
    // delete[] field_values;
}


// Flat index calculation for the field_values vector.
template <typename T>
size_t LatticeField<T>::get_flat_idx(size_t i0, size_t i1, size_t i2, size_t i3) const {
    return i0 * (dim1 * dim2 * dim3) + i1 * (dim2 * dim3) + i2 * dim3 + i3;
}


// Const version of operator()
template <typename T>
const T& LatticeField<T>::operator()(size_t i0, size_t i1, size_t i2, size_t i3) const {
    return field_values[get_flat_idx(i0, i1, i2, i3)];
}


// Implementation of the randomize with distribution and generator method.
template <typename T>
template <typename Distribution, typename Generator>
void LatticeField<T>::randomize(Distribution& distribution, Generator& generator) {
    // Fill field_values with random values
    for (auto &elem : field_values) {
        elem = distribution(generator);
    }
}


// Implementation of the randomize method.
template <typename T>
void LatticeField<T>::randomize_sequential() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::function<T(std::mt19937&)> dis;

    if constexpr (std::is_integral<T>::value) {
        auto dist = std::uniform_int_distribution<T>(0, 100);
        dis = [dist](std::mt19937& gen) mutable { return dist(gen); };
    } else if constexpr (std::is_floating_point<T>::value) {
        auto dist = std::uniform_real_distribution<T>(0.0, 1.0);
        dis = [dist](std::mt19937& gen) mutable { return dist(gen); };
    } else if constexpr (std::is_same<T, std::complex<float>>::value || std::is_same<T, std::complex<double>>::value) {
        auto dist = std::uniform_real_distribution<typename T::value_type>(0.0, 1.0);
        dis = [dist](std::mt19937& gen) mutable { return T(dist(gen), dist(gen)); };
    }

    // Fill field_values with random values
    for (auto &elem : field_values) {
        elem = dis(gen);
    }
}


// Implementation of the randomize method.
template <typename T>
void LatticeField<T>::randomize() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::function<T(std::mt19937&)> dis;

    if constexpr (std::is_integral<T>::value) {
        auto dist = std::uniform_int_distribution<T>(0, 100);
        dis = [dist](std::mt19937& gen) mutable { return dist(gen); };
    } else if constexpr (std::is_floating_point<T>::value) {
        auto dist = std::uniform_real_distribution<T>(0.0, 1.0);
        dis = [dist](std::mt19937& gen) mutable { return dist(gen); };
    } else if constexpr (std::is_same<T, std::complex<float>>::value || std::is_same<T, std::complex<double>>::value) {
        auto dist = std::uniform_real_distribution<typename T::value_type>(0.0, 1.0);
        dis = [dist](std::mt19937& gen) mutable { return T(dist(gen), dist(gen)); };
    }

    // Fill field_values with random values
    std::for_each(std::execution::par_unseq, field_values.begin(), field_values.end(), [&](T &elem) {
        elem = dis(gen);
    });
}


// Implementation of the fun method.
template <typename T>
void LatticeField<T>::apply_func(std::function<void(T&)> fun) {
    std::for_each(std::execution::par_unseq, field_values.begin(), field_values.end(), fun);
}


template <typename T>
void LatticeField<T>::apply_func_sequential(std::function<void(T&)> fun) {
    for (auto &elem : field_values) {
        fun(elem);
    }
}


// Implementation of the reduce_if method.
template <typename T>
T LatticeField<T>::reduce_if(std::function<bool(const T&)> predicate, T init,
                                      std::function<T(const T&, const T&)> binary_op) {
    return std::transform_reduce(
        std::execution::par_unseq,
        field_values.begin(),
        field_values.end(),
        init,
        binary_op,
        [&](const T& value) { return predicate(value) ? value : T{}; }
    );
}


template <typename T>
T LatticeField<T>::reduce_if_sequential(std::function<bool(const T&)> predicate, T init,
                                      std::function<T(const T&, const T&)> binary_op) {
    for (const auto &value : field_values) {
        if (predicate(value)) {
            init = binary_op(init, value);
        }
    }
    return init;
}


// Explicit template instantiations
template class LatticeField<float>;
template class LatticeField<double>;
template class LatticeField<std::complex<float>>;
template class LatticeField<std::complex<double>>;
