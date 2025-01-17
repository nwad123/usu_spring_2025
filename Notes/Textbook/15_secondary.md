# Chapter 15 - Predicate Abstraction for Program Verification

- Basic algorithms for the verification of safety and termination of programs
- Two underlying concepts are:
  1. Predicate abstraction, and
  2. Counterexample-guided Abstraction Refinement

## Introduction

Program Verification Algorithms
: Algorithms that take a program and a correctness property and try to answer the question
of whether the program is correct.

Safety
: Non-reachability of error states.

Termination
: Program does not take infinite time.

## Definitions

Program
: Specified through formulas and a set of logical variables, $V$

Program Counter (PC)
: A distinguished program variable of every program, $ pc \in V $

## Reachability

A state $s$ is reachable if there exists a program computation $ s_1, s_2, ... $ that contains
$s$.

A program is safe if error states are unreachable.

## Binary Reachability

Extending the notion of reachability from states to _pairs of states_. A pair of states, 
$ (s, s`) $ is reachable if there is an execution where $s$ followed by $s`$ is reachable.

## 15.4.1 Safety via Inductiveness

In order to check reachability, we construct a set of reachable states, then apply a function over 
the set of states to generate the _next_ possible reachable states. This process could technically 
be infinite (e.g. we have a loop and never reach deadlock states), but we can counter this by showing 
that the set is closed under the _next_ function. This would show the set is inductive.

```python
def next(s):
    if not 4 in s:
        s.add(4)

a: set[int] = {1, 2, 3}

print(a) # {1, 2, 3}

next(a)
print(a) # {1, 2, 3, 4}

next(a)
print(a) # {1, 2, 3, 4}
         # at this point `a` is inductive because repeated application of 
         # `next()` does not change it at all
```

Since our _states_ and our _transistions_ are represented by formulas, we can use the `post` function 
given by the paper to derive the next state formula given a transition formula and a state formula.

$$ post(state, transistion) = \exists V`` : state[ V`` / V ] \and transistion[ V`` / V][ V / V` ]$$ 

Or in english, there exists a program $V``$ such that $V$ in state can be replaced with $V``$ and 
$V$ is replaced by $V``$ in transistion, followed by $V`$ being replaced by $V$.

For example:

If our program variables are ` V = { pc, x, y, z } `, our starting state is `at_l2 && y >= z`, and 
our transistion is `goto(l2, l2) && x+1<=y && x=x+1 && unchanged(y,z)`, we could apply post as follows:

_See page 455 in the textbook, I decided it was too much to type_

We calculate all of the reachable state formulas by applying $post$ to an initial formula with all the 
transitions, and then applying all the transistions to a new formula, and so on and so forth until we 
have found all the states (or we loop for infinity). We then form the disjunction of all of these formulas 
together to form a reachable equation.

We then can create another equation that represents the inductive safety invariant. Applying $post$ to 
the inductive safety invariant must be inductive, that is, you cannot go to a new state from the the 
inductive safety variant, you must stay within the set of states specified. Also, the safety invariant 
must not contain any error states. In equation form you could say that `invariant && error |= false` 
(invariant and error equations entail false).

Basically, this whole section shows how if you generate the reachable states, if none of them are error
states, then you are good to go.

## 15.4.2 Termination via inductiveness 

Composing transistion formulas:

$$ \rho_1 \dot \rho_2 = \exists V`` : \rho_1[ V`` / V`] \and \rho_2[ V`` / V ] $$

See page 458 for the recursive version. If we apply the recursive version we get a transistion invariant 
that is characterized by using iteration of relational composition.

The restriction of program transistion relation is given by `transistion && reachable`, where `transistions`
is the transistion formulas for the system and `reachable` is the reachability forumalas for the system.

A program terminates iff the restriction `transistion && reachable` is well-founded.

Well-founded 
: A binary relation $\psi$ is _well-founded_ if it does not generate any infinite sequence $s_1, s_2, ...$
such that $(s_i, s_{i+1}) \in \psi \forall i \in 1, 2, ...$. (Page 453)

## 15.5 Abstraction

One problem with the approach given in 15.4.1 is that "in many cases" (Page 460) the iteration will never 
stop and new states will continue to be generated.

_Page 459 contains an example that shows how our example program could generate this_

### 15.5.1 Safety and Predicate Abstraction

We can create a overapproximation of all the reachable states, called $ \phi_{reach}^{\#} $. Since this is 
a superset, if the superset doesn't contain any error states, then the original set also will not contain any 
error states.

To get this overapproximation, we'll derive another $post$ function, $post^{\#}$. $post^{\#}$ is calculated in
two steps:

1. Apply $post$ 
2. Overapproximate the results using a function $\alpha$

The overapproximation function can be completed by setting a finite set of predicates, $Pred$, and then 
performing the following:

$$ \alpha(\phi) = \and \{ p \in Preds | \phi \entails p \} $$

If the set of entailed predicates, $ \{ p \in Preds | \phi \entails p \} $, is empty, the result is $ true $
which is the weakest (most overapproximated) abstraction.

> Maybe try implementing some of this in SymPy?


