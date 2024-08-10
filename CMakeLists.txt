cmake_minimum_required(VERSION 3.20)

# Set the project name
project(OpenQCD++ LANGUAGES CXX CUDA)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)  # This is necessary for the std::execution policies.
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify the NVIDIA HPC SDK compilers
set(CMAKE_C_COMPILER "nvc")
set(CMAKE_CXX_COMPILER "nvc++")
set(CMAKE_CUDA_COMPILER "nvcc")

# Find CUDA
find_package(CUDA REQUIRED)

# Ensure the NVIDIA C++ compiler is used with GPU support
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdpar=gpu")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdpar=gpu")

# List of module source files
set(MODULES_SOURCES
    modules/lattice/LatticeField.cpp
)

# Function to add an executable with proper settings
function(add_gpu_executable NAME)
    add_executable(${NAME} ${ARGN})
    target_include_directories(${NAME} PRIVATE include)
    target_compile_options(${NAME} PRIVATE -stdpar=gpu)
    target_link_options(${NAME} PRIVATE -stdpar=gpu)
endfunction()

# Add the executables
add_gpu_executable(print_tests app/latticeField_tests/print_tests.cpp ${MODULES_SOURCES})
add_gpu_executable(randomize app/parallel_computations/randomize.cpp ${MODULES_SOURCES})
add_gpu_executable(apply_func app/parallel_computations/apply_func.cpp ${MODULES_SOURCES})
add_gpu_executable(reduce_if app/parallel_computations/reduce_if.cpp ${MODULES_SOURCES})