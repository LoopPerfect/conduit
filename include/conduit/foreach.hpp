#ifndef CONDUIT_FOR_EACH_HPP
#define CONDUIT_FOR_EACH_HPP

#include <conduit/meta.hpp>
#include <conduit/seq.hpp>

namespace conduit {
namespace F {
template<class Xs, class Task>
auto forEach(Xs xs, Task task) -> seq<decltype(first(xs))> {
  for (auto x: xs) {
    task(x);
    co_yield x;
  }
};
}

auto forEach = [](auto task) {
  return [task](auto&&xs) -> seq<decltype(first(xs))> {
    return F::forEach(FWD(xs), task);
  };
};

}

#endif
