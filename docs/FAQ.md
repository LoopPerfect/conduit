# FAQ

## Why do you have a function template implementation and a lambda version of each operator?

 * Clang's Coroutine-TS implementation is experimental and buggy.
 * Composing operators that are coroutine lambdas segfaults the compiler.

## Why does find return a sequence instead of one optional?

This way is more composable. 

## How can I pass a mutable functor to zipWith, startWith and alike?

We strongly believe in seperating pure code from code with side-effects. If you have side-effects in your computational pipeline then it can be very hard to reason about your application. When building big functional reactive systems with Rx we learned that this creates a lot of confusion and subtle bugs. Discouraging side- effects enforces more generic components.

## How does this differ from Rx?

Rx allows you to build and transform *push* based data processing pipelines. Conduit is a *pull* based system.

## How does this differ to Range-V3 ?

Range-V3 focuses on implementing an API compatible with the Ranges-TS. Although there is some intersection between Range-V3 and Conduit's Sequences API, Conduit's API is much leaner. This enables more composability and compiler optimizations. 

### Why does `seq` not implement `.base()` ? 

`.base()` returns the pointer to the original iterator. For example: 

```c++
  //pseudo code
  std::vector nums = {1,2,3};
  auto it = (nums 
   >> map([](auto x){ return x+1;))
   >> find([](auto x) { return x == 2;}))
    .base();

  nums.begin() == it;
```

This function encourages place-oriented programming and requires significant book-keeping to implement. 

It is also not possible to implement it cleanly for every operator. For example, `zip` and `scan` do not have a 1:1 mapping from the elements in the originating iterators to the returned iterator. 

In short, `.base()`: 

 - Makes sequences/ranges non-monadic, which makes them less composable.
 - Has negative performance implications as every value must be in memory for a pointer to point to it.
 - Makes it easier to write unsafe code through dangling pointers 
 - Increases complexity as it increases the API surface that each operator needs to implement.
 - Forces you to express your algorithms in terms of iterators instead of just values.

We haven't yet seen any cases where a usage of `.base()` cannot be replaced with the other operators. If you have one, please let us know in the issue tracker; we would love to discuss it! :smile: 
