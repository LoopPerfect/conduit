#ifndef CONDUIT_COMPOSE_HPP
#define CONDUIT_COMPOSE_HPP

#include "meta.hpp"

namespace conduit {

template <class X, class F>
auto evaluate(X&& x, F f) -> decltype(f(FWD(x))) {
  return f(FWD(x));
}

template <class X, class F, class... Fs>
auto evaluate(X&& x, F f, Fs&&... fs)
  -> decltype(evaluate(f(FWD(x)), FWD(fs)...)) {
  return evaluate(f(FWD(x)), FWD(fs)...);
}

template <class... Fs>
auto compose(Fs&&... fs) {
  return [=](auto&& x) -> decltype(evaluate(FWD(x), fs...)) {
    return evaluate(FWD(x), fs...);
  };
}

namespace operators {
template <class Xs, class F>
auto operator>>(Xs&& xs, F&& f)
  -> decltype(xs.begin(), f(FWD(xs)).begin(), f(FWD(xs))) {
  return f(FWD(xs));
}

} // namespace operators
} // namespace conduit

#endif
