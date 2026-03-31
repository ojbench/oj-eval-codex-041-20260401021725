#ifndef SJTU_UTILITY_HPP
#define SJTU_UTILITY_HPP

#include <utility>

namespace sjtu {

// Make sjtu::pair fully compatible with std::pair by aliasing.
// This ensures iterator value_type and operator-> interoperate safely
// with std::map-backed implementations.
template<class T1, class T2>
using pair = std::pair<T1, T2>;

} // namespace sjtu

#endif
