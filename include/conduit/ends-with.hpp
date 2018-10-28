#ifndef CONDUIT_ENDS_WITH_HPP
#define CONDUIT_ENDS_WITH_HPP

#include "concat.hpp"

namespace conduit {

auto endsWith = [](auto&&xs) {
  return [xs = FWD(xs)](auto&& ys) mutable { 
    return F::concat(FWD(ys), std::move(xs)); 
  };
};

} // namespace conduit

#endif
