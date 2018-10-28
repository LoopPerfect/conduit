#ifndef CONDUIT_FIND_HPP
#define CONDUIT_FIND_HPP

#include "meta.hpp"
#include "seq.hpp"

namespace conduit {
namespace F {
auto find = [](auto xs, auto f) -> seq<decltype(first(xs))> {
  for (auto x : xs) {
    if (f(x)) {
      co_yield x;
      break;
    }
  }
};
}

auto find = [](auto f) {
  return [f](auto&& xs) { 
    return F::find(FWD(xs), f); 
  };
};

} // namespace conduit

#endif
