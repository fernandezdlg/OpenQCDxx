# Set the compiler
CXX = g++-14
CXXFLAGS = -std=c++23 -O2 -I/opt/homebrew/include/eigen3 -I../../include

# Find all .cpp files in the current directory
SRC = $(wildcard *.cpp)

# Output executable
TARGETS = $(SRC:.cpp=)

# Default target
all: $(TARGETS)

# Rule to compile and link in one step
%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Clean up build files
clean:
	rm -f $(TARGETS)

# Run the tests
run: $(TARGETS)
	@for target in $(TARGETS); do ./$$target; done
