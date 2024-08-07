#include <iostream>
#include "mdarray.h"


// Example. use case
int main() {
    constexpr std::size_t d0 = 5;
    constexpr std::size_t d1 = 4;
    constexpr std::size_t d2 = 3;
    constexpr std::size_t d3 = 2;

    mdarray<int, d0, d1, d2, d3> arr;

    // Initialize to the sum of the indices.
    for (std::size_t i = 0; i < d0; ++i) {
        for (std::size_t j = 0; j < d1; ++j) {
            for (std::size_t k = 0; k < d2; ++k) {
                for (std::size_t l = 0; l < d3; ++l) {
                    arr[i][j][k][l] = i + j + k + l;
                }
            }
        }
    }

    // Print some sample elements:
    std::cout << "arr[0][0][0][0]: " << arr[0][0][0][0] << std::endl;
    std::cout << "arr[1][2][1][0]: " << arr[1][2][1][0] << std::endl;
    std::cout << "arr[4][3][2][1]: " << arr[4][3][2][1] << std::endl;

    // TODO: Maybe add a size() method to the mdarray type such that the following works:
    // auto size = arr.size(0);
    // auto size = arr.size(1);
    // auto size = arr.size(2);
    // auto size = arr.size(3);
    std::cout << "Size 0 of arr: " << arr.size() << std::endl;
    std::cout << "Size 1 of arr: " << arr[0].size() << std::endl;
    std::cout << "Size 2 of arr: " << arr[0][0].size() << std::endl;
    std::cout << "Size 3 of arr: " << arr[0][0][0].size() << std::endl;
    return 0;
}

