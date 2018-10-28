#ifndef CONDUIT_CONCAT_HPP
#define CONDUIT_CONCAT_HPP

#include "meta.hpp"
#include "seq.hpp"

namespace conduit {
namespace F {

template<class Xs>
auto concat(Xs&& xs) -> Xs&& {
  return FWD(xs);
}
 
template<class Xs, class...Ys>
auto concat(Xs xs, Ys... ys) -> seq<decltype(first(xs))> {
  for (auto x : xs) {
    co_yield x;
  }

  if constexpr (sizeof...(ys)) {
    for (auto x : concat(std::move(ys)...)) {
      co_yield x;
    }
  }
}

}

auto concat = [](auto&&...xs) {
  return F::concat(FWD(xs)...);
};

} // namespace conduit

#endif
