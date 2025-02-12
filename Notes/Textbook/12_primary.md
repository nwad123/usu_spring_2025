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
              assert(x == 1)); // {x = 1}
              });
    
    thread M2([&](){
              assert(x >= 0);  // {x >= 0 }
              x = 2;           //  x := 2
              assert(x == 2)); // {x = 2}
              });

    M1.join();
    M2.join();
}
```

No, otherwise this would be a bad example for demonstrating the owicki-gries method.

Also, point out that in serial we can totally compose using Hoare logic. The point of this 
section is that Hoare logic is not good for parallel composition.

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

---

## 12.2.1 The (Non-compositional) Owicki-Gries Method 

The issue of composing processes as described on pg. 348 comes from Hoare logic being 
good for sequential, not parallel composition. The paper gives an example of why this is. 
To adapt Hoare logic to parallel composition you need to add _another_ proof rule, that of 
"non-interference". 

Non-Interference Condition 
: If $$ M_1 || M_2 $$ then no statement of $$ M_2 $$ should change an assertion in the proof 
outline of M1, and vice versa.
: A statement $S$ with pre-condition $P$ in a proof outline for $M_1$ _does not interfere_ 
with an assertion $A$ in a proof outline for $M_2$ if the Hoare triple 
$$ 
\{ P \and A \} S \{ A \}
$$
holds. Informally interpreted, this means that any transistion $S$ from any state satisfying 
$$ 
\{ P \and A \}
$$
does not falsify $A$.

For _N_ statements and assertions, checking non-interference has a complexity of 
$$ 
O(N^2)
$$

---

Technically the Owicki-Gries method is not completely compositional, as the non-interference 
property has to be added on the side. However, if you just change all of the triples to 
"proof outlines" apparently it is compositional.

The problem arises when you want to calculate interference-free proofs. This is very hard by 
hand, so the authors outline an automated solution.

--- 

## 12.2.2 Localized Inductive Invariants 

---

### 12.2.2.1 The Shared-Variable Program Model 

This models concurrency similar to how _imperative_ languages such as C, C++, Java, and Rust 
view memory in a single program. Memory is shared between many (possibly) concurrent threads 
of execution.

Program 
: Given by a tuple 
$$
(V, I, T)
$$
where $V$ is a finite set of program variables, $I(V)$ is a set of initial states, and 
$T(V, V^{\prime}$ defines as successor relation, with $V^{\prime}$ and isomorphic 
copy of $V$.

Isomorphic
: A structure-preserving mapping between two structures of the same type that can be reversed 
by an inverse mapping [Wikipedia, Isomorphism](https://en.wikipedia.org/wiki/Isomorphism)

Strongest Post-Condition Predicate Transformer ($post$)
: States that are successors of $T$ and satisfy the squiggly.

Component 
: A piece of a program that is typically represented by a Hoare triple.
