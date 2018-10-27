#ifndef CONDUIT_MAP_HPP
#define CONDUIT_MAP_HPP

#include "meta.hpp"
#include "seq.hpp"

namespace conduit {
namespace F {
auto map = [](auto g,
              auto f) -> seq<decltype(id(f(*g.begin())))> {
  for (auto x : g) {
    co_yield f(x);
  }
};
}

auto map = [](auto&& f) {
  return [f](auto&& g) { return F::map(FWD(g), f); };
};

} // namespace conduit

#endif
