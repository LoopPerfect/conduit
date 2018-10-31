#ifndef CONDUIT_TO_VECTOR_HPP
#define CONDUIT_TO_VECTOR_HPP

#include <vector>

namespace conduit {
auto toVector = [](std::size_t n=0) {
  return [n](auto&& xs) -> std::vector<decltype(first(xs))> {
    using T = decltype(first(xs));
    auto vec = std::vector<T>();
    vec.reserve(n);
    for (auto&&x: xs) {
      vec.emplace_back(std::move(x));
    }
    return vec;
  };
};
}

#endif
