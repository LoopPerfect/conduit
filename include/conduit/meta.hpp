#ifndef CONDUIT_META_HPP
#define CONDUIT_META_HPP

#include <type_traits>
#define FWD(x) std::forward<decltype(x)>(x)

namespace conduit {

template <class T>
T id(T const& x) {
  return x;
}

} // namespace conduit

#endif
