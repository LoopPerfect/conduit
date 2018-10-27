
#include <experimental/coroutine>
#include <type_traits>
#include <stack>
#include <vector>

#define FWD(x) std::forward<decltype(x)>(x)

namespace conduit {

using namespace std::experimental;

template<class T>
struct seq;

template<class T>
struct promise {
  T value;

  template<class U>
  auto yield_value(U&& value) -> decltype( 
    (this->value = value),
    suspend_always{}
  ) {
    this->value = value;
    return {};
  }

  suspend_always initial_suspend() { return {}; }
  suspend_always final_suspend() { return {}; }
  seq<T> get_return_object() { return {this}; };
    
  void unhandled_exception() { std::terminate(); }
  void return_void() {}
};

template<class T>
struct iterator {
  coroutine_handle<promise<T>> handle;

  iterator& operator++() {
    handle.resume();
    return *this;
  }

  T&& take() {
    return std::move(handle.promise().value);
  }

  constexpr T const& value() const noexcept {
    return handle.promise().value;
  }

  constexpr bool done() const noexcept {
    return handle && handle.done();
  }

  constexpr bool operator==(iterator const& rhs) const noexcept {
    return done() == rhs.done();
  }

  constexpr bool operator!=(iterator const& rhs) const noexcept { 
    return done() != rhs.done();
  }
  
  T const& operator*() const { 
    return handle.promise().value; 
  }
  
  T const* operator->() const { 
    return &(operator*()); 
  }
};


template <typename T> 
struct seq {
  using iterator_type = iterator<T>;
  using promise_type = promise<T>;
  using handle_type = coroutine_handle<promise_type>;

  iterator_type begin() {
    p.resume();
    return {p};
  }

  iterator_type end() { 
    return {nullptr}; 
  }

  seq(seq<T>&& rhs) 
    : p(rhs.p) { 
    rhs.p = nullptr; 
  }

  ~seq() {
    if (p)
      p.destroy();
  }

  T&& take() {
    return std::move(p.promise().value);
  }

  T& get() {
    return p.promise().value;
  }

  T const& get() const {
    return p.promise().value;
  }

  bool next() {
    p.resume();
    return !p.done();
  }

  seq(promise_type* p) : p{
    coroutine_handle<promise_type>::from_promise(*p)
  } {}

  coroutine_handle<promise_type> p;
};

}
