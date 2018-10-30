#ifndef CONDUIT_FILTER_HPP
#define CONDUIT_FILTER_HPP

#include <conduit/meta.hpp>
#include <conduit/seq.hpp>

namespace conduit {
namespace F {
auto filter = [](auto xs, auto f) -> seq<decltype(first(xs))> {
  for (auto x : xs) {
    if (f(x))
      co_yield x;
  }
};
}

auto filter = [](auto&& f) {
  return [f](auto&& xs) { 
    return F::filter(FWD(xs), f); 
  };
};

} // namespace conduit

#endif
