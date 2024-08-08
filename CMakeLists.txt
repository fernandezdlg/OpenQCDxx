cmake_minimum_required(VERSION 3.20)

# Set the project name
project(OpenQCD++)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)  # This is necessary for the std::execution policies.
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify the compilers
set(CMAKE_C_COMPILER "gcc-14")
set(CMAKE_CXX_COMPILER "g++-14")

# Ensure the GCC standard library is used
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

# List of module source files
set(MODULE_SOURCES
    modules/lattice/LatticeField.cpp
)

# Add the executables
add_executable(print_tests app/latticeField_tests/print_tests.cpp ${MODULES_SOURCES})
add_executable(randomize app/parallel_computations/randomize.cpp ${MODULES_SOURCES})
add_executable(apply_func app/parallel_computations/apply_func.cpp ${MODULES_SOURCES})
add_executable(reduce_if app/parallel_computations/reduce_if.cpp ${MODULES_SOURCES})

# Include directories
target_include_directories(randomize PRIVATE include)
target_include_directories(apply_func PRIVATE include)
target_include_directories(reduce_if PRIVATE include)
