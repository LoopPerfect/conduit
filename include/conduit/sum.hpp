#ifndef CONDUIT_SUM_HPP
#define CONDUIT_SUM_HPP

#include <conduit/meta.hpp>
#include <conduit/seq.hpp>

namespace conduit {

static constexpr auto sum() { 
  return [=](auto&& xs) {
    using T = decltype(first(xs)); 
    T result = T{}; 
    for (auto&&x: xs) {
      result+=x;
    } 
    return result;
  }; 
};

} // namespace conduit

#endif
