
#include <iostream>
#include <random>
#include "random/ranlxs.h"


int main() {

    Ranlxs<> default_ranlxs{1}; // Uses default p = 223, r = 23
    std::cout << "Generated number: " << default_ranlxs() << std::endl;

    Ranlxs<24, 10> custom_ranlxs{1}; // Uses custom p = 24, r = 10
    std::cout << "Generated number: " << custom_ranlxs() << std::endl;

    std::ranlux24 ranlux24{1};
    std::cout << "Generated number: " << static_cast<float>(ranlux24()) / (uint_fast32_t{1} << 24) << std::endl;

    return 0;
}
