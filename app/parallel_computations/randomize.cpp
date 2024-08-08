// This program performs some examples of the parallel computations that can be done with the
// LatticeField class.
// As examples, this performs and times:
// - Randomization of a lattice field.

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

    std::ofstream csv_file("randomize_times.csv");
    csv_file << "Randomization_par_unseq [ms], Randomization_seq [ms]\n";

    for (int i = 0; i < 100; ++i) {
        // Create a lattice field of size 4x4x4x4 with initial value 0.0
        LatticeField<double> lattice(8, 8, 8, 8, 0.0);

        // Parallel Randomize the lattice field
        const auto start = high_resolution_clock::now();
        lattice.randomize();
        const auto end = high_resolution_clock::now();
        auto timed_randomize_parallel = duration_cast<microseconds>(end - start).count();

        // Randomize the lattice field
        auto start_time = high_resolution_clock::now();
        lattice.randomize_sequential();
        auto end_time = high_resolution_clock::now();
        auto timed_randomize_sequential = duration_cast<microseconds>(end_time - start_time).count();

        // Write the times to the CSV file
        csv_file << timed_randomize_parallel << "," << timed_randomize_sequential << "\n";
    }

    csv_file.close();
    std::cout << "Timing results have been written to timing_results.csv" << std::endl;

    return 0;
}