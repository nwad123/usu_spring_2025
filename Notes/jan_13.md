# Terms and Definitions

## Architectures

1. Single CPU
   - Input/Output is direct
   - Memory access is singlular
2. Multiple CPU
   - Shared memory: each core can access the _same_ memory as the other cores
   - Distributed memory: each core has it's _own_ memory
     - A messaging system may need to be used to read/write data between cores

Register
: Fast storage internal to a processor

Program counter
: Stores the next instruction that will take place

Bus
: On-chip data transfer between different nodes (memory, cores, accelerators, etc.)

## Splitting a Program Into Tasks - Processes and Threads

Operating System "Process"
: An _instance_ of a computer program that is being executed.

- Threads
  - A _thread_ is contained within a _process_, and allow programmers to divide a
    program into separate tasks.
  - Creating a thread is called a _fork_
  - Joining two threads is called a _join_

> Why would we choose _threads_ over _processes_?
>
> _Processes_ are managed by the OS, and therefore have more overhead and requirements than
> a thread has. _Threads_ are considered "light-weight" and typically cost less to create
> a thread than a process.

## Caches

Memory Bottleneck (von Neumann bottleneck)
: The issue when operations take less time than a memory bus, resulting in down time while
data is being transferred from memory to the processor

Memory Caches
: Memory that can be accessed _faster_ than main memory

## Locality

Spatial Locality
: Accessing a nearby location

Temportal Locality
: Accessing in the near future

```cpp
/* { Example of Spatial Locality } */

std::array<float, 1000> z;

// ...

// Using for-loop
float sum{ 0.0f };
for (const auto i : z) {
    sum += i;
}

// Using algorithms
const auto sum = std::reduce(std::cbegin(z), std::cend(z), 0.0f, std::plus{});
```

When we perform the first access the cache line pointed to by `z.data()` is pulled into the
cache so that we aren't reaching into main memory for every element of `z`.

- Cache coherency
  - An issue that occurs when a variable is written into the cache by not main memory
  - Write-through cache: data in main memory is updated when a value in cache is updated
  - Write-back cache: data written back to main memory _only_ when cache line is replaced

### Caches and Matrix Multiply

```cpp
double a[MAX][MAX], x[MAX], y[MAX];

// first loop iteration
// more friendly for caches beceause the index `A[i][j]`
for (const auto i : iota(0, MAX))
    for (const auto j : iota(0, MAX))
        y[i] += A[i][j] * x[j];

// second loop iteration
for (const auto j : iota(0, MAX))
    for (const auto i : iota(0, MAX))
        y[i] += A[i][j] * x[j];

```

