#ifndef CONDUIT_SCAN_HPP
#define CONDUIT_SCAN_HPP

#include "meta.hpp"
#include "seq.hpp"

namespace conduit {
namespace F {
auto scan = [](auto state, auto xs, auto f) -> seq<decltype(id(f(state, first(xs))))> {
  co_yield state;
  for (auto x : xs) {
    state = f(state, x);
    co_yield state;
  }
};
}

auto scan = [](auto&& initialState, auto&& f) { 
  return [=](auto&& xs) { 
    return F::scan(initialState, FWD(xs), f); 
  }; 
};

} // namespace conduit

#endif
