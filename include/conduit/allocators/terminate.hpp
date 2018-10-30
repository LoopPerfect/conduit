#ifndef CONDUIT_ALLOCATORS_TERMINATE_HPP
#define CONDUIT_ALLOCATORS_TERMINATE_HPP
#include <conduit/seq.hpp>

namespace conduit {

template<class T>
struct promise_allocator;

template<class T>
struct promise_allocator<promise<T>> {
  static void* alloc(std::size_t n) {
    std::terminate();
  }

  static void dealloc(void* p) {
    std::free(p);
  }
};

}

#endif
