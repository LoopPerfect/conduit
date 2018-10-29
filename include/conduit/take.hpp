#ifndef CONDUIT_TAKE_HPP
#define CONDUIT_TAKE_HPP

#include "meta.hpp"
#include "seq.hpp"

namespace conduit {
namespace F {
template<class Xs>
auto take(Xs xs, unsigned n) -> seq<decltype(first(xs))> {
  if (!n) co_return;
  for (auto x: xs) {
    co_yield x;
    if (--n == 0) 
      break;
  }
};
}

auto take = [](unsigned n) {
  return [n](auto&& xs) { 
    return F::take(FWD(xs), n); 
  };
};

} // namespace conduit

#endif
