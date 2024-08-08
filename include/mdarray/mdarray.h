// TODO: FIXME: This header file templates a multidimensional array for use in lattice fields.
// This should be replaced with a fuller std::mdarray in a hopefully not so distant C++ standard.
// Cf. https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/p1684r5.html
#include <array>
#include <algorithm>


// Type alias for multi-dimensional array
template <typename T, std::size_t... sizes>
struct mdarray_impl;


// This recursively instantiates the template arguments and creates a nested std::array type.
template <typename T, std::size_t dim_i, std::size_t... dim_ixx>
struct mdarray_impl<T, dim_i, dim_ixx...> {
    using type = std::array<typename mdarray_impl<T, dim_ixx...>::type, dim_i>;
};


// Base case.
template <class T, std::size_t dim_i>
struct mdarray_impl<T, dim_i> {
    using type = std::array<T, dim_i>;
};


// TODO: This would be changed to the std::mdarray type in a future C++ standard.
template <typename T, std::size_t... sizes>
using mdarray = typename mdarray_impl<T, sizes...>::type;


// Function template to fill the mdarray with a stream of numbers
// template <typename T, std::size_t size, std::size_t... sizes, typename InputIt>
// void fill_mdarray_with_iterator(mdarray<T, size, sizes...>& arr, InputIt& it) {
//     for (auto& sub_arr : arr) {
//         fill_mdarray_with_iterator(sub_arr, it);
//     }
// }

// // Base case for the innermost array with iterator
// template <typename T, std::size_t size, typename InputIt>
// void fill_mdarray_with_iterator(mdarray<T, size>& arr, InputIt& it) {
//     for (auto& elem : arr) {
//         elem = *it;
//         ++it;
//     }
// }

// Function template to fill the mdarray with a default value
// FIXME: This is buggy.
// template <typename T, std::size_t dim_i, std::size_t... dim_ixx>
// void fill_mdarray_with_value(mdarray_impl<T, dim_i, dim_ixx...>& arr, const T& init_value) {
//     for (auto& sub_arr : arr) {
//         fill_mdarray_with_value<T, dim_ixx...>(sub_arr, init_value); // Recursive call
//     }
// }

// Function to fill with default value on 4D array
template <typename T, std::size_t dim_0, std::size_t dim_1, std::size_t dim_2, std::size_t dim_3>
void fill_mdarray_with_value_4d(mdarray<T, dim_0, dim_1, dim_2, dim_3>& arr, const T& init_value) {
    for (auto& sub_arr_3d : arr) {
        for (auto& sub_arr_2d : sub_arr_3d) {
            for (auto& sub_arr_1d : sub_arr_2d) {
                std::fill(sub_arr_1d.begin(), sub_arr_1d.end(), init_value); // Fill innermost array
            }
        }
    }
}

// Base case for the innermost array
template <typename T, std::size_t dim_i>
void fill_mdarray_with_value(std::array<T, dim_i>& arr, const T& init_value) {
    std::fill(arr.begin(), arr.end(), init_value); // Fill innermost array
}



// Function to fill a 4D array with a stream of numbers (e.g. for randomly generated data)
template <typename T, std::size_t dim_0, std::size_t dim_1, std::size_t dim_2, std::size_t dim_3, typename InputIt>
void fill_mdarray_with_iterator_4d(mdarray<T, dim_0, dim_1, dim_2, dim_3>& arr, InputIt& it) {
    for (auto& sub_arr_3d : arr) {
        for (auto& sub_arr_2d : sub_arr_3d) {
            for (auto& sub_arr_1d : sub_arr_2d) {
                for (auto& elem : sub_arr_1d) {
                    elem = *it;
                    ++it;
                }
            }
        }
    }
}







// // Function template to fill the mdarray with a default value
// template <typename T, std::size_t size, std::size_t... sizes>
// void fill_mdarray_with_value(mdarray<T, size, sizes...>& arr, const T& init_value) {
//     for (auto& sub_arr : arr) {
//         fill_mdarray_with_value(sub_arr, init_value); // Recursive call
//     }
// }

// // Base case for the innermost array
// template <typename T, std::size_t size>
// void fill_mdarray_with_value(std::array<T, size>& arr, const T& init_value) {
//     std::fill(arr.begin(), arr.end(), init_value); // Fill innermost array
// }

