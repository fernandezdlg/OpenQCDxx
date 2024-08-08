// This program performs some examples of the parallel computations that can be done with the
// LatticeField class.
// As examples, this performs and times:
// - Parallel reduction of the lattice field (values greater than 0.5 only).


#include "lattice/LatticeField.h"
#include <complex>
#include <chrono>
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <functional>

int main() {
    using namespace std::chrono;

    std::ofstream csv_file("reduce_if_times.csv");
    csv_file << "Parallel_reduce_if [ms],Sequential_reduce_if [ms]\n";

    for (int i = 0; i < 100; ++i) {
        // Create a lattice field of size 8x8x8x8 with initial value 0.0
        LatticeField<double> lattice(8, 8, 8, 8, 0.0);

        // Randomize the lattice field
        lattice.randomize();

        // Perform parallel reduction of the lattice field (values greater than 0.5 only)
        const auto start_parallel = high_resolution_clock::now();
        double sum_parallel = lattice.reduce_if(
            [](const double& val) { return val > 0.5; },
            0.0,
            [](const double& a, const double& b) { return a + b; }
        );
        const auto end_parallel = high_resolution_clock::now();
        auto timed_parallel_reduce = duration_cast<microseconds>(end_parallel - start_parallel).count();

        // Randomize the lattice field
        lattice.randomize();

        // Perform sequential reduction of the lattice field (values greater than 0.5 only)
        const auto start_sequential = high_resolution_clock::now();
        double sum_sequential = lattice.reduce_if_sequential(
            [](const double& val) { return val > 0.5; },
            0.0,
            [](const double& a, const double& b) { return a + b; }
        );
        const auto end_sequential = high_resolution_clock::now();
        auto timed_sequential_reduce = duration_cast<microseconds>(end_sequential - start_sequential).count();

        // Write the times to the CSV file
        csv_file << timed_parallel_reduce << "," << timed_sequential_reduce << "\n";
    }

    csv_file.close();
    std::cout << "Timing results have been written to reduce_if_times.csv" << std::endl;

    return 0;
}
