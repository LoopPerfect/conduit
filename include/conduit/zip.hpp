#ifndef CONDUIT_ZIP_HPP
#define CONDUIT_ZIP_HPP

#include "meta.hpp"
#include "seq.hpp"
#include <tuple>

namespace conduit {

namespace detail {
auto rangeUndone = [](auto&g) {
  auto& [_,b,e] = g;
  return b!=e;
};

auto all = [](auto...c) {
  return (c && ... && true); 
};

template<class F, class...Xs>
auto zip(F f, Xs...xs) -> seq<decltype(f(*std::get<1>(xs)...))> {
  using namespace detail;
  while ( all(rangeUndone(xs)...) ) {
    co_yield f(*std::get<1>(xs)...);
    (++std::get<1>(xs) , ... , 0); 
  }
}
}

namespace F {
template<class F, class...Xs>
auto zip(F&&f, Xs&&...xs) -> seq<decltype(id(f(first(xs)...)))> {
  return detail::zip(
      FWD(f),
      std::tuple<
        decltype(id(xs)),
        decltype(id(xs).begin()),
        decltype(id(xs).end())> {
          std::move(xs), 
          xs.begin(), 
          xs.end()
        }...
  );
};
}


auto zip = [](auto&&f, auto&&...xs) {
  return F::zip(FWD(f), FWD(xs)...);
};

auto zipWith = [](auto&&xs, auto f) {
  return [xs = FWD(xs), f](auto&& ys) {
    return zip(std::move(f), std::move(xs), FWD(ys));
  };
};

} // namespace conduit

#endif
