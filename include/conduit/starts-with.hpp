#ifndef CONDUIT_STARTS_WITH_HPP
#define CONDUIT_STARTS_WITH_HPP

#include <conduit/concat.hpp>

namespace conduit {

auto startsWith = [](auto...xsf) {
  return [=](auto&& ys) mutable { 
    return F::concat(xsf()..., FWD(ys)); 
  };
};

} // namespace conduit

#endif
