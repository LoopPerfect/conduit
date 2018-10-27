#ifndef CONDUIT_FILTER_HPP
#define CONDUIT_FILTER_HPP

#include "meta.hpp"
#include "seq.hpp"

namespace conduit {
namespace F {
auto filter = [](auto g, auto f) -> seq<decltype(id(*g.begin()))> {
  for (auto x : g) {
    if (f(x))
      co_yield x;
  }
};
}

auto filter = [](auto&& f) {
  return [f](auto&& g) { 
    return F::filter(FWD(g), f); 
  };
};

} // namespace conduit

#endif
