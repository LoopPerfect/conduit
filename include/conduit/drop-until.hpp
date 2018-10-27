#ifndef CONDUIT_DROP_UNTIL_HPP
#define CONDUIT_DROP_UNTIL_HPP

#include "meta.hpp"
#include "seq.hpp"

namespace conduit {
namespace F {
auto dropUntil = [](auto g, auto f) -> seq<decltype(id(*g.begin()))> {
  auto it = g.begin();
  auto e = g.end();

  while (it != e) {
    auto x = *it;
    if (f(x)) {
      break;
    }
    ++it;
  }

  while (it != e) {
    co_yield *it;
    ++it;
  }
};
}

auto dropUntil = [](auto&& f) {
  return [f](auto&& g) { 
    return F::dropUntil(FWD(g), f); 
  };
};

} // namespace conduit

#endif
