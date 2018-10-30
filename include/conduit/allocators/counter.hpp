#ifndef CONDUIT_ALLOCATORS_COUNTING_HPP
#define CONDUIT_ALLOCATORS_COUNTING_HPP
#include <conduit/seq.hpp>

namespace conduit {

template<class T>
struct promise_allocator;

thread_local static long alloc_count = 0;

static void reset_alloc_counter() {
  alloc_count = 0;
} 

static long get_alloc_counter() {
  return alloc_count;
}


template<class T>
struct promise_allocator<promise<T>> {
  static void* alloc(std::size_t n) {
    ++alloc_count;
    return std::malloc(n);
  }

  static void dealloc(void* p) {
    std::free(p);
  }
};

}

#endif
