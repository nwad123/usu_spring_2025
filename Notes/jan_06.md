# Course Overview

## Tools we will learn

1. Posix threads / C++ threads
    - Aside: What are coroutines? Are they a thread? Do they fit into HPC?
2. OpenMP
    - An API for C/C++ parallel applications
3. Message-Passing Interface (MPI)
    - Standard
    - Aside: Related to Erlang?
4. CUDA

## Code Sourcing

We can use code from other sources, as long as we follow plaguarism rules.

# Why High Performance Computing?

1. Makes a performance difference
2. Improves throughput
3. Single-core systems are slowing down
    - Moore's law harder to maintain
    - Dennard scaling did not include leakage current and threshold voltage, so 
        that means clock speeds could not infinitely scale.
    - Around 2006 processors hit a "power wall" and couldn't scale past 4 GHz

Solution to slowing down single core performance is adding multiple cores 
but then you run into the issue of slow, shared resources, such as:

- I/O 
- Networks 
- On-chip communication

HPC directly used for:

1. Big data
2. Simulation and Modelling

# Challenges with HPC

1. Serial algorithms and programs are not easily converted to parallel 

## Example with a Reduction Algorithm 

```cpp 
auto n = /* ... */;
auto sum = 0;

for (auto x : iota(0, n)) {
    sum += compute_value(/* ... */);
}
```

This is a serial process, how would we split it up for more? Maybe have each 
core do some amount of work.

```cpp 
auto n = {{0, 5}, {6, 10}, /* ... */ {n - 4, n}};

auto partial = [](auto range) {
    auto partial_sum = 0;

    for (auto x : range) {
        parital_sum += compute_value(/* ... */);
    }
}

vector<thread> threads;

for (auto range : n) {
    threads.push_back(partial, range);
}

auto sum = 0;

/* collect partials from threads */
```
