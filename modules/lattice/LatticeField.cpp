#include "lattice/LatticeField.h"
#include "common_utilities.h"
#include <random>
#include <algorithm>
#include <execution>
#include <numeric>


// Constructor implementation.
template <typename T>
LatticeField<T>::LatticeField(
        const size_t dim0,
        const size_t dim1,
        const size_t dim2,
        const size_t dim3,
        const T init_value
) : dim0(dim0),
    dim1(dim1),
    dim2(dim2),
    dim3(dim3),
    volume(dim0 * dim1 * dim2 * dim3) {
        // Initialize std::vector<T> field_values to init_value
        field_values.resize(volume, init_value);
    }


// Non-const version of operator()
template <typename T>
T& LatticeField<T>::operator()(size_t i0, size_t i1, size_t i2, size_t i3) {
    size_t index = i0 * (dim1 * dim2 * dim3) + i1 * (dim2 * dim3) + i2 * dim3 + i3;
    return field_values[index];
}


// Const version of operator()
template <typename T>
const T& LatticeField<T>::operator()(size_t i0, size_t i1, size_t i2, size_t i3) const {
    size_t index = i0 * (dim1 * dim2 * dim3) + i1 * (dim2 * dim3) + i2 * dim3 + i3;
    return field_values[index];
}


// Implementation of the get_flat_idx method.
template <typename T>
size_t LatticeField<T>::get_flat_idx(size_t i0, size_t i1, size_t i2, size_t i3) const {
    return i0 * (dim1 * dim2 * dim3) + i1 * (dim2 * dim3) + i2 * dim3 + i3;
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
    } else {
        static_assert(always_false<T>::value, "Unsupported type");
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
    } else {
        static_assert(always_false<T>::value, "Unsupported type");
    }

    // Fill field_values with random values
    std::for_each(std::execution::par_unseq, field_values.begin(), field_values.end(), [&](T &elem) {
        elem = dis(gen);
    });
}


// Implementation of the fun method.
template <typename T>
void LatticeField<T>::func(std::function<void(T&)> fun) {
    std::for_each(std::execution::par_unseq, field_values.begin(), field_values.end(), fun);
}
template <typename T>
void LatticeField<T>::func_sequential(std::function<void(T&)> fun) {
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
