#include <iostream>
#include <conduit/conduit.hpp>

using namespace conduit;
using namespace operators;

auto squares = []() -> seq<int> {
  int x = 0;

  while ( true ) {
    co_yield x * x;

    ++x;
  }
};

int main() {
  for (auto x : squares() >> take(10)) {
    std::cout << x << std::endl;
  }

  return 0;
}
