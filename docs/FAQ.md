# FAQ

## Why do you have a function template implementation and a lambda version of each operator ?

Clangs Coroutine-TS implementation is experimental and buggy.
Composing operators that are coroutine lambdas segfaults the compiler.

## Why does find return a sequence instead of one optional ?

This way is more composable. 

## How can I pass a mutable functor to zipWith, startWith and alike ?

We strongly believe in purity. 
If you have sideeffects in your computational pipeline it is very hard to reason about your application.
When building big functional reactive systems with Rx we learned that this creates a lot of confusion and suddle bugs. Discuraging sideeffects enforces more generic components.

## How does this differ to Rx ?

Rx allows you to build and transform *push* based data processing pipelines.
Conduit is a *pull* based system.

## How does this differ to Range-V3 ?

Range-V3 focuses to implement a API compatible with the Ranges-TS.
Although there is an intersection between Range-V3 and Conduit's Sequences API.
Conduit's API is much leaner enabling more composability and optimization.

### Why does Seq not implement `.base()` ? 

`.base()` returns the pointer to the original iterator. eg.:

```c++
  //pseudo code
  std::vector nums = {1,2,3};
  auto it = (nums 
   >> map([](auto x){ return x+1;))
   >> find([](auto x) { return x == 2;}))
    .base();

  nums.begin() == it;
```

`.base()` bookkeeping and encurages place-oriented programming.
Requiring to point to an originating iterator is prohibits operators that don't have an exact 1:1 mapping eg.:
zip or scan.

This has several big caveats:
 - It makes sequences/ranges non-monadic which makes it less composable.
 - It has negative performance implications as it every value be in memory so a pointer can point to it.
 - It enables you to write unsafe code, enabling to create dangling pointers 
 - It increases complexity as it increases the API surface that each operator needs to implement.
 - it forces you to express your algorithms in terms of iterators instead of just values.

