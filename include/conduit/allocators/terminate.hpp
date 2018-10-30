#ifndef CONDUIT_ALLOCATORS_TERMINATE_HPP
#define CONDUIT_ALLOCATORS_TERMINATE_HPP

#ifdef CONDUIT_CUSTOM_ALLOCATOR
#error "Only one custom allocator may be defined"
#endif

#define CONDUIT_CUSTOM_ALLOCATOR 1

#include <conduit/allocators/default.hpp>
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
