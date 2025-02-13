# OpenMP Shared Memory Programming

Cyclic scheduling
: Denoted by the `schedule(static, 1)` which indicates that at compile time the schedule
for the parallel process is computed. This is a round-robin style approach with a batch
size of 1.

Example of Cyclic Scheduling:

```cpp
auto elements = {0, 1, 2, 3, 4, 5, 6};
auto num_threads = 3;

#pragma omp parallel for /*...*/ schedule(static, 1)
/*...*/
```

Given the above code, the schedule will be as follows:

| Thead | Elements |
| :---: | :------: |
|   0   |   0, 3   |
|   0   |   1, 4   |
|   0   |   2, 6   |

Dynamic Scheduling 
: Input is broken up into "chunks" with size `s`, and then when each thread is ready 
to compute a value it requests a new chunk. This is good for dynamic runtime systems 
where the input size is not known beforehand. An overhead is associated with the 
dispatching system.

Guided Scheduling 
: A kind of dynamic scheduling where the size of the chunks _decreases_ overtime. 
This can help ensure that threads do a similiar amount of work, even if the time taken 
to compute a chunk of work is not constant.

## OMP Environment Variables

Best practice is to use the `OMP_SCHEDULE` environment variable to be able to set 
the scheduling of your program without recompiling your code.

# Directives (Again)

```cpp 
#pragma omp barrier // Creates a barrier 
#pragma omp atomic  // Creates an atomic op
#pragma omp critical(name) // creates a _named_ critical section
```
