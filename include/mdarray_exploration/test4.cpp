#include <iostream>
#include <random>
#include <vector>
#include "mdarray.h"

int main() {
    // Define the dimensions
    constexpr std::size_t dim_0 = 4,
                          dim_1 = 4,
                          dim_2 = 3,
                          dim_3 = 25;

    mdarray<double, dim_0, dim_1, dim_2, dim_3> arr;

    // Create a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> dis(0.0, 1.0); // mu = 0, stdev = 1

    // Generate a stream of random numbers
    std::vector<double> random_numbers;
    for (std::size_t i = 0; i < dim_0 * dim_1 * dim_2 * dim_3; ++i) {
        random_numbers.push_back(dis(gen));
    }

    // Fill the mdarray with the random numbers
    auto it = random_numbers.begin();
    fill_mdarray_with_iterator_4d<double, dim_0, dim_1, dim_2, dim_3>(arr, it);

    // Print the first couple of elements to verify
    for (size_t i3 = 0; i3 < dim_3; i3++) {
        std::cout << arr[0][0][0][i3] << std::endl;
    }

    return 0;
}