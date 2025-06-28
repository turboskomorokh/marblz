//
// Created by paul on 28.06.25.
//

#ifndef IN_BETWEEN_H
#define IN_BETWEEN_H

#include <type_traits>

namespace utils {
  template<typename T>
  constexpr bool in_between(const T &value, const T &min, const T &max) {
    static_assert(std::is_arithmetic_v<T>, "is_between requires arithmetic type");
    return (min <= max)
             ? (value >= min && value <= max)
             : (value >= max && value <= min);
  }
}
#endif //IN_BETWEEN_H
