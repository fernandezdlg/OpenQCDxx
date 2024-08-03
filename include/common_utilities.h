#ifndef COMMON_UTILITIES_H
#define COMMON_UTILITIES_H

// Helper template to trigger static_assert for unsupported types
template <typename T>
struct always_false : std::false_type {};

#endif // COMMON_UTILITIES_H