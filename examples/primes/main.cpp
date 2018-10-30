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


auto primes = [] {
  return range()
    >> map([](auto i) RET(3+i*2) ) // create a seqence of odd nums > 2
    >> flatMap([primes = vector<int>()](auto c) mutable RET ( 
      primes // divide each candidate by the primes we encountered
        >> take(primes.size())
        >> find([c](auto p) RET (c % p == 0)) // search and stop if divisible
        >> count() // find yields at most 1 element, count how many we got (starts with zero)
        >> orElse(just(c)) // if we didn't find any, its a prime. yield it
        >> find([](auto x) RET (x)) // filter out zeros yielded by find+count or take prime
        >> forEach([&](auto p) {
          primes.push_back(p);  // update list of primes
        }) // Note: lifetime of primes-vector is bound to the coroutine  
    )) 
    
    >> startsWith(just(2)); // two is the only even prime
};

int main() {
  auto items = primes() 
    >> take(10)
    >> zipWith(range, [](auto x, auto y) { 
      return tuple{x, y};
    });

  for (auto [i, n] : items) {
    std::cout << n << std::endl;
  }

  return 0;
}
