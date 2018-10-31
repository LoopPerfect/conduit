# Allocators 

The current implementation of coroutines implicitly allocates a coroutine - unless optimized - on the heap.
As a result the user cannot initialize any coroutines using a custom allocator object.

This means only static allocators can be supported.
One way to costumize the allocation behaviour is via an extra template parameter `seq<T, AllocatorType>`.

An alternative is to implement a costomization point using template specializations.

We have chosen the latter solution as this does not require threading the AllocatorType through each operator.
We believe that this reduces the cognitive overhead required to implement new algorithms and will increase developer productivity.
This solution implies that you have to choose an allocator seq<T> before your application runs.

## How does the customization point work?

We have defined a generic type `template<class T> promise_allocator` which is used for each `seq<T>`.
By default it uses the standard allocator. 
In order to change the promise_allocator specialize this template:

```c++
template<class T>
struct promise_allocator<seq<T>> {
  void* allocate(std::size_t);
  void deallocate(void*);
};
```

This definition will be prefrred by the compiler as this a higher specificity compared to default definition.
You can use a predifined allocator by just including `include/conduit/allocators/*.hpp` or implement your own in a same fashion.
