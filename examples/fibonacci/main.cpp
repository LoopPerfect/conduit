#include <tuple>
#include <vector>
#include <iostream>

#include <conduit/compose.hpp>
#include <conduit/map.hpp>
#include <conduit/count.hpp>
#include <conduit/flatmap.hpp>
#include <conduit/foreach.hpp>
#include <conduit/starts-with.hpp>
#include <conduit/take.hpp>
#include <conduit/find.hpp>
#include <conduit/just.hpp>
#include <conduit/range.hpp>
#include <conduit/or-else.hpp>
#include <conduit/zip.hpp>

using std::vector;
using std::tuple;
using std::tie;
using namespace conduit;
using namespace operators;

#define RET(X) { return X; }

auto fib = []() -> seq<int> {
  auto a = 0; 
  auto b = 1;
  while ( true ) {
    co_yield a;
    tie(a, b) = tuple{a + b, a};
  }
};

int main() {

  auto items = fib() 
    >> take(5)
    >> zipWith(range, [](auto x, auto y) { 
      return tuple{x, y};
    });

  for (auto [i, n] : items) {
    std::cout << n << std::endl;
  }

  return 0;
}
