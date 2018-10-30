#ifndef CONDUIT_SEQ_HPP
#define CONDUIT_SEQ_HPP

#include <experimental/coroutine>
#include <type_traits>
#include <cassert>
#include <conduit/meta.hpp>
#include <conduit/allocators/default.hpp>

using namespace std::experimental;

namespace conduit {


template<class T>
struct seq;

template <class T>
struct promise {
  T value;

  void* operator new(std::size_t n) {
    using A = promise_allocator<promise<T>>;
    return A::alloc(n);
  }

  void operator delete(void* p) {
    using A = promise_allocator<promise<T>>;
    A::dealloc((promise<T>*)p);
  }
  
  template <class U>
  auto yield_value(U&&value)
    -> decltype((this->value = FWD(value)), suspend_always{}) {
    this->value = FWD(value);
    return {};
  }

  constexpr suspend_always initial_suspend()const { return {}; }
  constexpr suspend_always final_suspend()const { return {}; }
  constexpr seq<T> get_return_object() noexcept {
    return {this}; 
  };

  void unhandled_exception() const { std::terminate(); }
  void return_void() const {}
};

template <class T>
struct iterator {
  coroutine_handle<promise<T>> handle;

  iterator& operator++() {
    assert(handle != nullptr);
    assert(!handle.done());
    if(handle)
      handle.resume();
    return *this;
  }

  T&& take() { return std::move(handle.promise().value); }

  constexpr T value() const noexcept { return handle.promise().value; }

  constexpr bool done() const noexcept { return !handle || handle.done(); }

  constexpr bool operator==(iterator const& rhs) const noexcept {
    return done() == rhs.done();
  }

  constexpr bool operator!=(iterator const& rhs) const noexcept {
    return done() != rhs.done();
  }

  T const& operator*() const { return handle.promise().value; }
  T& operator*() { return handle.promise().value; }

  T const* operator->() const { return &(operator*()); }
};

template <class T>
struct seq {
  using iterator_type = iterator<T>;
  using promise_type = promise<T>;
  using handle_type = coroutine_handle<promise_type>;

  iterator_type begin() {
    if (p) p.resume();
    return {p};
  }

  iterator_type end() { return {nullptr}; }

  seq(seq<T> const&) = delete;
  seq(seq<T>&& rhs)
    : p(rhs.p) {
      rhs.p = nullptr;
  }

  ~seq() {
    if (p) {
      p.destroy();
    }
  }

  T&& take() { return std::move(p.promise().value); }

  T const& get() const { return p.promise().value; }
  T& get() { return p.promise().value; }

  bool next() {
    assert(p != nullptr);
    assert(!p.done());
    p.resume();
    return !p.done();
  }

private:
  friend struct promise<T>;
  seq(promise_type* promise)
    : p{coroutine_handle<promise_type>::from_promise(*promise)} 
  {}

  coroutine_handle<promise_type> p;
};

} // namespace conduit

#endif
