#ifndef CONDUIT_RANGE_HPP
#define CONDUIT_RANGE_HPP

#include <conduit/meta.hpp>
#include <conduit/seq.hpp>

namespace conduit {

namespace detail {
template<class B, class E, class S>
auto range(B i, E e, S step) -> seq<B> {
  while (i < e) {
    co_yield i;
    i += step;
  }
};

template<class B, class E>
auto range(B i, E e) -> seq<B> {
  while (i < e) {
    co_yield i;
    ++i;
  }
};

template<class B = unsigned long>
auto range(B i = 0) -> seq<B> {
  while (true) {
    co_yield i;
    ++i;
  }
};
}

auto range = [](auto...args) -> decltype(
  detail::range(args...)
) {
  return detail::range(args...);
};

}

#endif
