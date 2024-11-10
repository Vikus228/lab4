#ifndef CONCEPTS_H
#define CONCEPTS_H

#include <type_traits>

template <typename T>
concept Number = std::is_integral_v<T> || std::is_floating_point_v<T>;

#endif // CONCEPTS_H
