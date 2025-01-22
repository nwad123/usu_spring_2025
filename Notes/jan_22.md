# Parallel Software 

Shared Memory Programs 
: Single process that forks several times to carry out tasks (variables shared between threads)

Distributed Memory Programs 
: Multiple processes are created to carry out tasks (no memory conflicts)

Single Program Multiple Data (SPMD)
: A single executable that can behave as if it were multiple different programs through the use 
  of conditional branches
  
## Writing Parallel Programs 

1. Divide the work up 
   - so each thread gets the same work 
   - communication is minimized
2. Arrange for the processes/threads to synchronize
3. Arrange for communication

## Threads 

Basic function of how threads actually get compiled into machine code in a single executable:

```
if (I'm thread i) then 
  do my thing 
else 
  do another thing
```

_C++ threads and pthreads (and other threading impls) just abstract away this functionality_

Dynamic Threads 
: Threads are created and destroyed on an "as-needed" basis, which is efficient, but introduces 
  overhead everytime a new thread is created

Static Threads 
: Pool of threads created and are allocated work and are only terminated at cleanup, this gives 
  us a set of threads that are ready to go whenever, which gives us better performance (usually) 
  but may leave us with a bunch of idle threads

Non-determinism
: Unless forced by the programmer (not the hardware) threads can execute in whatever order they 
  want, leading to a non-deterministic output

Race Condition 
: Different threads are reading / writing a shared variable at the same time 

Mutex (Mutual Exclusion)
: Allow only one thread / process at a time to read and / or write a variable

Example of using a `std::mutex` to guarantee serial addition of the shared global variable 
`our_val`.

```cpp
// ... running on thread i 

/* local */ my_val = some_value();

my_mutex.lock();
/* global */ our_val += my_val;
my_mutex.unlock();
```

## Pthreads 

See documentation.

## C++ 11 `std::thread`

See documentation.
