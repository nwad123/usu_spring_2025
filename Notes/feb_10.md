# OpenMP Continued

Using `#pragma omp parallel /* ... *./` creates threads and destroys threads bound to 
the scope following the directive. That means that if you do something like:

```cpp
#pragma omp parallel for num_threads(100)
for(size_t i; i < 1000; i++) {
    /* operation */
}
```

It will attempt to create _100 threads_ before the for loop and then destroy 100 threads 
after. This is kinda expensive, so make sure that threads are created and destroyed in 
a good place for performance.

# OpenMP Scope 

The _scope_ of a variable refers to the set of threads that can access the variable in 
a parallel block.

Shared Scope 
: Can be accessed by _all_ threads 

Private Scope 
: Can be accessed by only _one_ thread 

Default scope for OpenMP is _shared_. It's good practice to always use `default(none)` in
order to not accidentally use shared variables.

# Parallel Sort 

For functions operating on memory we run into issues with a shared dependency between 
two threads swapping elements in an array.

## Tranposition Sort 

Each thread inspects two elements and sorts them. See the slides for a nice diagram of it.
