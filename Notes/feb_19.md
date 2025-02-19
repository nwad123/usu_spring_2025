# SMT 

First Order Logic
: Add predicates, functions, and quantifiers to propositional logic 

Satisfiable / Unsatisfiable 
: Similar to the exists quantifiers

Principle of Duality 
: If we reverse all 0's to 1's and vice versa _and_ also replace all or's 
with and's and vice versa the new statement should hold.

Completeness of Propositional Logic
: CNF is the same as Product of Sums, this is better for proving something.
  For this we mainly rely on CDCL.
: DNF is the same as Sum of Products, this is good for generating counter
  examples if you know that you will be able to generate a counter 
  example early.

The solving approach usually involves transforming the logic into DNF and 
then incrementally checking the formula.

## Lazy - SMT Algorithm 

```python
def lazy_smt(phi: qff) -> Sat | Unsat:
    F = a(phi) # `a` is something about applying the alphabet 
    
    while True:
        A = get_model(F) 

        if A is None:
            return Unsat 

        else:
            mu = check_sat(A)
            if mu is Sat:
                return Sat
            else 
                F = F and not a(mu)
```

## Rectangle Fitting Example 

Break a problem down into a description and let SMT solve it. Basically 
this becomes a placement problem.

## $\sigma$-Theory T 

The signature defines what can be in the theory, and the theory is specified 
by $ T = (\sigma, A) $ where $A$ is the class of $\sigma$-models $A$.
