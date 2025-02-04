# Threads Review

Barriers
: We use these when we need to ensure that all partial results have been computed.

Condition Variables
: Synchonization mechanism (found in C++) use mutex on the background.

# Read-write Locks

Consider the case where we are using a linked list. If multiple threads are trying to write to the linked list 
(such as `insert` or `delete`) then pointers could be invalidated. To solve this issue we could possibly 
try to have locks depending on what kind of operation you need to do.

## Option 1:

Add locks around all functions:

```cpp
unique_lock<mutex> lock{};
/* function (contains, insert, delete, read iteration) */
lock.unlock();
```

This basically serializes all accesses, and may be good if most of the time you are calling insert and delete, 
but if you're doing read iterations a lot you won't exploit parallelism.

## Option 2:

Add a mutex per node. This kills performance (and potentially memory size) for read functions. But it would 
allow for finer write access.

## Option 3:

`PThread` read-write locks provide another option. Option 1 only allows one thread to access the entire list 
at any instant, while option 2 allows any thread to only access one node at any instance.

This is basically the borrow checker. There can be one writer at any time, or multiple readers.

# Thread Safety

Problems with threads:

- Data race 
- Dead lock 

> Example: `strtok`
> `strtok` works by caching a pointer at the beginning, and then finding matches after that. The issue 
> is that the caching is _not_ thread safe, because each thread can cause a different string to be 
> cached, which is bad news.

For any function to be thread safe, it cannot use _another_ function that is not thread safe. 

Re-entrant Functions 
: A function that can be paused and restarted without thread issues.
