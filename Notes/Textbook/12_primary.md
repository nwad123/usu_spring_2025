# Compositional Reasoning 

Why do we even want compositional reasoning?

> State explosion is a _fundamental challenge_ for model checking methods... 
> Compositional reasoning is a technique which aims to \[lessen\] the effects of 
> state explosion on models.
> 
> pg. 345, emphasis added

## 12.1 Introduction

> Concurrent programs are PSPACE-HARD in _N_, where _N_ is the number of concurrently 
> active components available in the program.
>
> pg. 345 

---

Other names for "compositional reasoning" are: 

- Assume-guarantee reasoning 
- Local reasoning 
- Modular reasoning 
- Assume-commitment reasoning 
- Rely-guarantee reasoning 

The "essence of the principle" is to replace _global_ analysis with analysis of a single 
component of the system where the rest of the system is abstracted away into an 
_assumption_. "Proof rules" are laid out to ensure that assumptions and guarantees line 
up across the whole system.

(pg. 346) 

---

Through the chapter there are two types of concurrency discussed:

- Components communicate through shared memory 
- Component communicate through buffer-less message passing 

The _focus_ of the chapter is on algorithms which automatically construct assumptions 
used to make compositional rules.

(pg. 346)

---

# The Two "Core Principles" of Compositional Reasoning

$$
\{a\} M \{g\} 
$$

1. Transitivity: If $M$ satisfies 

   $$
   \{a\} M \{g\} 
   $$

   and $N$ satisfies 
   
   $$
   \{true\} N \{a\} 
   $$

   then the implication is that

   $$
   N || M 
   $$ 

   holds. This applies when assumptions and guarantees are _acyclic_.

2. Mutual induction: When we have circular rules, we can turn to induction. Not much 
   information is given on this in the introduction, I assume it's covered more later 
   on.

---

# 12.2 Reasoning With Assertions 

Will the example below _always_ run successfully? (Adapted from pg. 348)

```cpp
#include <thread>
#include <cassert>

using std::thread;

auto main() -> int 
{
    int x = 0; // var x: integer; initially x == 0

    thread M1([&](){
              assert(x >= 0);  // {x >= 0 }
              x = 1;           //  x := 1 
              assert(x == 1)); // {x = 1});
    
    thread M2([&](){
              assert(x >= 0);  // {x >= 0 }
              x = 2;           //  x := 2
              assert(x == 2)); // {x = 2});

    M1.join();
    M2.join();
}
```

No, otherwise this would be a bad example for demonstrating the owicki-gries method.

Possible paths of execution:

```cpp
// Happy path
x = 1; assert(x == 1); /* ... */ x = 2; assert(x == 2); /* SUCCESS */

// Tragic path
x = 1; x = 2; assert(x == 1); /* FAILURE */
```

Mathematically speaking, we also run into tragidy. If we try to apply Hoare's composition 
rules to this, we run into a post condition of $false$. See textbook for more information
on that.
