#ifndef CONDUIT_FLATMAP_HPP
#define CONDUIT_FLATMAP_HPP

#include "meta.hpp"
#include "seq.hpp"

namespace conduit {
namespace F {
auto flatMap = [](auto xs, auto f) 
  -> seq<decltype(first(f(first(xs))))> {
  for (auto x : xs) {
    for(auto y: f(x)) {
      co_yield y;
    }
  }
};
}

auto flatMap = [](auto&& f) { 
  return [f](auto&& xs) { 
    return F::flatMap(FWD(xs), f); 
  }; 
};

} // namespace conduit

#endif
