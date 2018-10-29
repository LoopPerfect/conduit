# How do Coroutines work?

## What is a Coroutine?

A coroutine is a function that can be suspended and resumed.
A function is a coroutine if it uses co\_yield, co\_return or co\_await.
Any co_\* keyword defines a suspension point

```c++

auto generateSequence() -> seq<int> {
  int i = 0;
  while (i) 
    co_yield i;
}

int main() {
  for(auto x: generateSequence()) {
    std::cout << x << std::endl;
    if(x>10) break;
  }
}

```


## How do coroutines interact with the compiler?

Everytime a function is invoked that uses any co_\* keywords the compiler will look at the returntype and search for the associated promise_type.

The promise_type is expected to be defined in the returntype or in the standartized extension point: 
```c++

template<class ReturnType, class...Args>
struct std::experimental::coroutine_traits<T, Args...> {
  struct promise_type {
    //....
  };
};

```

Template parameters match to the arguments of the called function. 

## What does the promise_type need to define ? 

```c++

struct promise_type {
  // return an avaitable eg: suspend_always{} or suspend_never{}
  //what should happen when coroutine invoked the first time
  auto initial_suspend() { return suspend_always{}; } 
  //what should happen when coroutine reached its end ?
  auto final_suspend() { return suspend_always{}; }

  // return a type that is convertible to the coroutine_type 
  auto get_return_object() {
    const handle = coroutine_handle<promise_type>::from_promise(*this);
    // this is accesible via handle.promise();
    return Coroutine_Type{ handle };
  }


  // this is your opportunity to store a value and make it accesible to the Coroutine_Type
  // invoked on co_yield value;
  // return an avaitable like initial_suspend
  auto yield_value(Value_Type)
  // invoked on co_return value;
  auto return_value(Value_Type) 
  // invoked on co_return;
  auto return_void() 
};

// coroutine_handle<T>::promise returns T&
// coroutine_handle<T>::done() // returns true if coroutine reached it's end.
// coroutine_handle<T>::resume() // resumes the coroutine
// coroutine_handle<T>::destroy() // destroys the coroutine

```

## How to Make a Coroutine Work with Range-Based-For-Loops ?

In order to enable interop with range-based-for-loops it needs to provide a *begin* and *end* methods.
Furthermore the returntype of *begin* and *end* needs to provide:
- `operator++` for advancing the coroutine
- `operator!=` for comparing the *begin* and *end* iterators. This is where you can 
- `operator*` for accesing the current_value of the sequence

Since C++17 the return types of begin and end may differ.
You may want to return an sentinel / thumbstone type to mark the end of the sequence.

```c++
  bool operator!=(sequence_iterator lhs, thumbstone) {
    return !lhs.done();
  }

``` 


