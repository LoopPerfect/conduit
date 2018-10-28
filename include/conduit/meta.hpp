#ifndef CONDUIT_META_HPP
#define CONDUIT_META_HPP

#include <type_traits>
#define FWD(x) std::forward<decltype(x)>(x)

namespace conduit {

template <class T>
T id(T const& x) {
  return x;
}

template <class T>
auto first(T&& xs) -> decltype(id(*xs.begin())) {
  return *xs.begin();
}


auto factory = [](auto sequence, auto...args) {
  return [=] {
    return sequence(args...);
  };
};

} // namespace conduit

#endif
