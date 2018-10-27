#ifndef CONDUIT_TAKE_WHILE_HPP
#define CONDUIT_TAKE_WHILE_HPP

#include "meta.hpp"
#include "seq.hpp"

namespace conduit {
namespace F {
auto takeWhile = [](auto g, auto f) -> seq<decltype(id(*g.begin()))> {
  for (auto x: g) {
    if (!f(x)) 
      break;
    co_yield x;
  }
};
}

auto takeWhile = [](auto&& f) {
  return [f](auto&& g) { 
    return F::takeWhile(FWD(g), f); 
  };
};

} // namespace conduit

#endif
