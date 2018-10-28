#ifndef CONDUIT_ENDS_WITH_HPP
#define CONDUIT_ENDS_WITH_HPP

#include "concat.hpp"

namespace conduit {

auto endsWith = [](auto...xsf) {
  return [=](auto&& ys) { 
    return F::concat(FWD(ys), xsf()...); 
  };
};

} // namespace conduit

#endif
