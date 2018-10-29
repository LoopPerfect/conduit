#ifndef CONDUIT_OR_ELSE_HPP
#define CONDUIT_OR_ELSE_HPP

#include "meta.hpp"
#include "seq.hpp"

namespace conduit {
namespace F {
template<class Xs, class Xsf>
auto orElse(Xs xs, Xsf xsf) -> seq<decltype(first(xs))> {
  bool hasElements = 0;
  for (auto x: xs) {
    hasElements = true;
    co_yield x;
  }

  if (!hasElements) {
    for (auto x: xsf()) {
      co_yield x;
    }
  }
}
}

auto orElse = [](auto xsf) {
  return [xsf](auto&&xs) {
    return F::orElse(FWD(xs), xsf);
  };
};


}

#endif
