# Predicate Abstraction - In Class Notes

How to get failure states?

- Specify good behavior instead of bad (`assert(true)`) this means that your failure
  states are represented by the inverse of your success states

Predicates
: "pre-selected formulas that define sets of states"

Logical Entailment 
: Same as logical implication `==>`

Deadlock State 
: A state with no successors 

Absorbing State 
: A state that only has transitions into itself 

$\rho_P$
: A "disjunction" of all transition relations

> Is the set of natural numbers $N$ closed under addition?
> Yes, because $ \forall x, y \in N, x + y \in N $.
>
> Subtraction?
> No, for example, $ 2 - 10 = - 8, \not \in N $.

Syntax $ \rho \[ V`` / V \] $
: Means that in $ \rho $ all $ V $ is replaced with $ V`` $

# Presenting Notes 

- Include reference back to page number and section from the book 
- Do examples on the board 
