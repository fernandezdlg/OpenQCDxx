// This program performs some examples of the parallel computations that can be done with the
// LatticeField class.
// As examples, this performs and times:
// - Parallel application of a function (an exp) to each element of the lattice field.

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

    std::ofstream csv_file("apply_func_times.csv");
    csv_file << "Parallel_exp [ms], Sequential_exp [ms]\n";

    for (int i = 0; i < 100; ++i) {
        // Create a lattice field of size 8x8x8x8 with initial value 0.0
        LatticeField<double> lattice(8, 8, 8, 8, 0.0);

        // Randomize the lattice field
        lattice.randomize();

        // Apply exp function to each element of the lattice field in parallel
        const auto start = high_resolution_clock::now();
        lattice.func([](double& val) {
            val = std::exp(val);
        });
        const auto end = high_resolution_clock::now();
        auto timed_parallel_exp = duration_cast<microseconds>(end - start).count();

        // Randomize the lattice field
        lattice.randomize();

        // Apply exp function to each element of the lattice field in parallel
        const auto start_s = high_resolution_clock::now();
        lattice.func_sequential([](double& val) {
            val = std::exp(val);
        });
        const auto end_s = high_resolution_clock::now();
        auto timed_seq_exp = duration_cast<microseconds>(end_s - start_s).count();


        // Write the times to the CSV file
        csv_file << timed_parallel_exp << ", " << timed_seq_exp << "\n";
    }

    csv_file.close();
    std::cout << "Timing results have been written to apply_func_times.csv" << std::endl;

    return 0;
}