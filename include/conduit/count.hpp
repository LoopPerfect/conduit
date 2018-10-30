#ifndef CONDUIT_COUNT_HPP
#define CONDUIT_COUNT_HPP

#include <conduit/meta.hpp>
#include <conduit/seq.hpp>

namespace conduit {

auto count = [](unsigned long start = 0) {
  return [start](auto xs) -> seq<unsigned long> {
    unsigned long i = start;
    for (auto x: xs) {
      (void)x;
      co_yield i;
      ++i;
    }
  };
};

}

#endif
