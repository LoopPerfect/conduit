#ifndef CONDUIT_MAP_HPP
#define CONDUIT_MAP_HPP

#include "meta.hpp"
#include "seq.hpp"

namespace conduit {
namespace F {
auto map = [](auto xs, auto f) -> seq<decltype(id(f(first(xs))))> {
  for (auto x : xs) {
    co_yield f(x);
  }
};
}

auto map = [](auto f) { 
  return [f](auto&& xs) { 
    return F::map(FWD(xs), f); 
  }; 
};

} // namespace conduit

#endif
