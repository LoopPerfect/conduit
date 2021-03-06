<p align="center">
  <img src="conduit.svg">
</p>

# Conduit ⚡

[![Travis](https://img.shields.io/travis/LoopPerfect/conduit.svg)](https://travis-ci.org/LoopPerfect/conduit) 
[![Godbolt](https://img.shields.io/badge/Godbolt-playground-blue.svg)](https://godbolt.org/z/wTRcvK)

Lazy High Performance Streams using Coroutine TS

Conduit is a utility library for building and transforming, ranges and lazy (infinite) iterable sequences. 

Conduit's goals are:

- 🎨 **Expressivity** 
- 🎶 **Composability**
- 🏃 **Performance**

These are attained by adopting a monadic interface that leverages zero-cost abstractions.

## Install

Download the header-only library bundle from the [releases page](https://github.com/LoopPerfect/conduit/releases). 

If you are using [Buckaroo](https://buckaroo.pm): 

```bash
buckaroo add github.com/LoopPerfect/conduit@branch=master
```

## Build

To fetch dependencies (only required for testing and benchmarks): 

```bash
buckaroo install
```

To build the library: 

```bash
buck build :conduit
```

To run the examples: 

```bash
buck run examples/primes
buck run examples/fibonacci
# etc...
```

To run the tests: 

```bash
buck test //...
```

## Examples

Use `co_yield` to define a coroutine and transform it using high-level operators.

```c++
using namespace std;
using namespace conduit;
using namespace conduit::operators;

auto fib = []() -> seq<int> {
  auto a = 0; 
  auto b = 1;
  while ( true ) {
    co_yield a;
    tie(a, b) = tuple{a + b, a};
  }
};

auto items = fib() 
  >> take(5)
  >> zipWith(range, [](auto x, auto y) { 
    return tuple{x, y};
  });

int vals[] = { 0, 1, 1, 2, 3, 5 };

for(auto [i, n] : items) {
  EXPECT_EQ(vals[i], n);
}

```

Construct elaborate algorithms using higher order operators:

```c++
#define RET(X) { return X; }

// sieve of eratosthenes
auto primes = [] {
  return range()
    >> map([](auto i) RET(3+i*2) ) // create a seqence of odd nums > 2
    >> flatMap([primes = vector<int>()](auto c) mutable RET ( 
      primes // divide each candidate by the primes we encountered
        >> find([c](auto p) RET (c % p == 0)) // search and stop if divisible
        >> count() // find yields at most 1 element, count how many we got (starts with zero)
        >> orElse(just(c)) // if we didn't find any, its a prime. yield it
        >> find([](auto x) RET (x)) // filter out zeros yielded by find+count or take prime
        >> forEach([&](auto p) {
          primes.push_back(p);  // update list of primes
        }) // Note: lifetime of primes-vector is bound to the coroutine  
    )) >> startsWith(just(2)); // two is the only even prime
};
```

## Support

Currently only `clang-7` with `-fcoroutines-ts` is supported.

MSVC support should be added in the near future.

## Contributions Welcome!

Head over to our [issue tracker](https://github.com/LoopPerfect/conduit/issues) to get involved in Conduit's development.
