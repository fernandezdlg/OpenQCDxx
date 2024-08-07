// Ex. 2 use case
#include <vector>
#include <iostream>
#include "mdarray.h"
#include <cstddef>
#include <iterator>
#include <algorithm>
#include <numeric>


int main() {

    // Define the dimensions
    constexpr std::size_t dim_0 = 4,
                          dim_1 = 4,
                          dim_2 = 3,
                          dim_3 = 2;

    mdarray<int, dim_0, dim_1, dim_2, dim_3> arr;

    // Fill the mdarray with a default value
    fill_mdarray_with_value_4d<int, dim_0, dim_1, dim_2, dim_3>(arr, 42);

    // Print the first element to verify
    std::cout << arr[0][0][0][0] << std::endl; // Should print 42

    // Now with a 1D array
    constexpr std::size_t dim_4 = 5;

    mdarray<int, dim_4> arr_1d;
    int default_value = 33;
    fill_mdarray_with_value(arr_1d, default_value);
    std::cout << arr_1d[0] << std::endl; // Should print 33
    return 0;
}