#ifndef CONDUIT_ALLOCATORS_DEFAULT_HPP
#define CONDUIT_ALLOCATORS_DEFAULT_HPP

#include <memory>

namespace conduit {
template<class T>
struct promise_allocator {
  static void* alloc(std::size_t n) {
    return std::malloc(n);
  }

  static void dealloc(void* p) {
    std::free(p);
  }
};
}

#endif
