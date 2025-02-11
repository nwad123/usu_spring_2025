See `9-OpenMP` for CHPC resources, also there are CHPC resources on canvas.

# OpenMP 

What is OpenMP and why is it so popular in HPC applications?

OpenMP 
: An API for shared memory parallel programming 
: MP stands for _multiprocessing_ 

OpenMP is used for systems where all processes and threads can share memory.

OpenMP is based around `#pragma`s to add non-standard behavior. Compilers that don't 
support the `#pragma`s will ignore them.

## Example 

This example shows how `Hello()` will be expanded to be called on `thread_count` threads.

```cpp
auto main() -> int 
{
    int thread_count = /* ... */ 

#   pragma omp parallel num_threads(thread_count) 
    Hello();

    return 0;
}
```

These pragmas apply directly to the line (or brace-enclosed block `{}`) directly after
the pragma.

You can check if your compiler supports OpenMP by the following:

```cpp
#ifdef _OPENMP 
#include <opm.h>
#endif 
```

That way if your compiler does _not_ support OpenMP you can run your program 
single-threadedly (as long as you also guard other calls to functions in `omp.h`).

## Pragmas 

### Parallel 

```cpp 
#pragma omp parallel
/*block*/
```

Most basic, runs the next expression in parallel across a number of threads. A clause, 
`num_threads` can be specified to set a desired thread count.

When this parallel block is called the original thread + the new threads are called a _team_,
and the original thread is the _master_ and the new threads are the _slaves_.

#### Clauses:

- `num_threads(integer)`: number of desired threads 
- `reduction(<operator>: <variable list>)`: a reduction on the given variable across the 
  specified operator

### Critical 

```cpp 
#pragma omp critial 
/*block*/
```

Makes a block as a critical section and only allows one thread to execute that line at a 
time.

### Parallel For 

_Same as MATLAB `parfor`_

```cpp 
#pragma omp parallel for /*clauses*/
/*for-loop block*/
```

Allows a for loop to be called in parallel (e.g. each loop iteration can be in paralell). 
We can combine this with `reduction` to make a easy reduction operation on some function.

The `for`-loop can't have _any_ statements put in it, only a subset of legal statements. 
Probably just look at the docs for more information.

### Private 

```cpp 
#pragma omp parallel for /*clauses*/ private(/*variable*/)
/*for-loop block*/
```

Marks private variables for each for loop.

### Shared

```cpp 
#pragma omp parallel for /*clauses*/ Shared(/*variable*/)
/*for-loop block*/
```

Marks shared variables for each for loop.

### Default 

```cpp 
#pragma omp parallel for /*clauses*/ default(/*variable*/)
/*for-loop block*/
```

Marks the default scope for variables. Using `default(none)` is good to ensure good 
compiler warning.

### Schedule 

```cpp 
#pragma omp parallel for /*clauses*/ schedule(/*variable*/)
/*for-loop block*/
```

Tells the compiler how to schedule the work on each thread.

## Data Dependencies for Loop Iterations

Sometimes if one loop iteration depends on previous loop iterations, then parallelizing 
the iterations can cause issues.

The simple fibonacci series accumulator is an example where this runs into a problem.
