#ifndef CONDUIT_TAKE_WHILE_HPP
#define CONDUIT_TAKE_WHILE_HPP

#include <conduit/meta.hpp>
#include <conduit/seq.hpp>

namespace conduit {
namespace F {
auto takeWhile = [](auto xs, auto f) -> seq<decltype(first(xs))> {
  for (auto x: xs) {
    if (!f(x)) 
      break;
    co_yield x;
  }
};
}

auto takeWhile = [](auto&& f) {
  return [f](auto&& xs) { 
    return F::takeWhile(FWD(xs), f); 
  };
};

} // namespace conduit

#endif
