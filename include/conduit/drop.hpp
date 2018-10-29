#ifndef CONDUIT_DROP_HPP
#define CONDUIT_DROP_HPP

#include "meta.hpp"
#include "seq.hpp"

namespace conduit {
namespace F {
template<class Xs>
auto drop(Xs xs, unsigned n) -> seq<decltype(first(xs))> {
  for (auto x: xs) {
    if (n) continue;
    co_yield x;
    --n;
  }
};
}

auto drop = [](unsigned n) {
  return [n](auto&& xs) { 
    return F::drop(FWD(xs), n); 
  };
};

} // namespace conduit

#endif
