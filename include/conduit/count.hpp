#ifndef CONDUIT_COUNT_HPP
#define CONDUIT_COUNT_HPP

#include "meta.hpp"
#include "seq.hpp"

namespace conduit {

auto count = [](auto x = 0) -> seq<decltype(x)> {
  while (1) {
    co_yield x;
    ++x;
  }
};
}

#endif
