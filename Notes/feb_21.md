# K - Induction

Example:

$$
K = 1, Tr\[ x_0, x_1\] \and P( x_0 ) \and \not P( x_1)
$$

If the above formula is _unsat_, then we show that over one inductive step
we are good to go.


$$
K = 2, Tr\[ x_0, x_1\] \and Tr\[ x_1, x_2 \] \and P( x_0 ) \and P( x_1 ) \and \not P( x_2)
$$

Here it is for k = 2. Again, if this is unsat P is inductive over 2 steps.

# DPLL

Basically an eager binary decision diagram (BDD) with backtracking.

Seems like you could do this on a gpu really quick? Maybe final project for HPC?

