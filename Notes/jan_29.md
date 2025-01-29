# Abstraction and Abstraction Refinement

Concrete
: The full model

Abstract
: The abstraction model, a superset of the concrete

Mutual Exclusion Formula:

$$
\forall G \not (C_1 \and C_2)
$$

Non-starvation Formula:

$$
\forall G ( T_i \rightarrow \forall F C_i )
$$

> Side Note: CTL cannot express all LTL, and LTL cannot express all CTL specifications.

Negation normal form 
: Negation should only be on variables, not statements

Least Fixed Point $\mu$
: The least element of a set of states where the state is an identity state with 
  function, $ F(s) = s $

Greatest Fixed Point $v$ 
: The greatest element of a set of states where the state is an identity state with 
  function $ F(s) = s $

