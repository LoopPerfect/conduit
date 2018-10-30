#ifndef CONDUIT_COMPOSE_HPP
#define CONDUIT_COMPOSE_HPP

#include <conduit/meta.hpp>

namespace conduit {

template <class X, class F>
auto evaluate(X&&x, F&& f) {
  return f(FWD(x));
}

template <class X, class F, class... Fs>
auto evaluate(X&&x, F&& f, Fs&&... fs) { 
  return evaluate( f(FWD(x)), FWD(fs)...);
}

template <class F, class... Fs>
auto compose(F f, Fs... fs) {
  return [=](auto&& x) {
    return evaluate(FWD(x), f, fs...);
  };
}

namespace operators {
template <class Xs, class F>
auto operator >> (Xs&& xs, F&& f)
  -> decltype(xs.begin(), f(FWD(xs)).begin(), f(FWD(xs))) {
  return f(FWD(xs));
}

} // namespace operators
} // namespace conduit

#endif

