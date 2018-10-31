#include <random>
#include <iostream>

#include <conduit/conduit.hpp>

using namespace conduit;
using namespace operators;

auto random_seq = [](int seed) -> seq<double> {
  // pseudo-random
  std::mt19937 engine(seed);
  std::uniform_real_distribution<> dist;

  while (true) {
    co_yield dist(engine);
  }
};

int main() {
  int seed = 1234;

  for (auto x : random_seq(seed) >> take(10)) {
    std::cout << x << std::endl;
  }

  return 0;
}
