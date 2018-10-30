#ifndef CONDUIT_DROP_UNTIL_HPP
#define CONDUIT_DROP_UNTIL_HPP

#include <conduit/meta.hpp>
#include <conduit/seq.hpp>

namespace conduit {
namespace F {
auto dropUntil = [](auto xs, auto f) -> seq<decltype(id(first(xs)))> {
  auto it = xs.begin();
  auto e = xs.end();

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
  return [f](auto&& xs) { 
    return F::dropUntil(FWD(xs), f); 
  };
};

} // namespace conduit

#endif
