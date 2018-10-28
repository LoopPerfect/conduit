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


template<class T>
struct capture {
  mutable std::remove_const_t<T> value;
  
  capture(T&& x) 
    : value(std::move(x))
  {}

  T&& take() const {
    return std::move(value);
  }
};

template<class T>
capture(T&&) -> capture<T>;

} // namespace conduit

#endif
