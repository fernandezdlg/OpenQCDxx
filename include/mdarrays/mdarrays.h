// TODO: FIXME: This header file templates a multidimensional array for use in lattice fields.
// This should be replaced with a fuller std::mdarray in a hopefully not so distant C++ standard.
// Cf. https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/p1684r5.html

#include <array>
#include <cstddef>

// This recursively instantiates the template arguments and creates a nested std::array type.
template <class T, std::size_t size, std::size_t... sizes>
struct ArrayHelper {
    using type = std::array<typename ArrayHelper<T, sizes...>::type, size>;
};

// Base case.
template <class T, std::size_t size>
struct ArrayHelper<T, size> {
    using type = std::array<T, size>;
};

// TODO: This would be changed to the std::mdarray type in a future C++ standard.
template <class T, std::size_t... sizes>
using mdarray = typename ArrayHelper<T, sizes...>::type;


// Ex. use case
// int main() {
//     mdarray<int, 5, 3, 4, 3> arr;
// }
