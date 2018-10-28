#ifndef CONDUIT_STARTS_WITH_HPP
#define CONDUIT_STARTS_WITH_HPP

#include "concat.hpp"

namespace conduit {

auto startsWith = [](auto&&xs) {
  return [xs = FWD(xs)](auto&& ys) mutable { 
    return F::concat(std::move(xs), FWD(ys)); 
  };
};

} // namespace conduit

#endif
