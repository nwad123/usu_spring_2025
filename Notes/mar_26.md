# Interpolation and Model Checking - "The Heck is Interpolation?"

Why does only Ken McMillian write about interpolation?

Interpolation
: Can be thought of a way of turning discrete data into continuous
  data.

## Logical Interpolation 

Typically, interpolation is thought of something done on the _reals_, but 
we want to do it with logic. Interpolation connects logical assertions that 
share a common value.

$$
\begin{split}
a \implies b \\
a \implies i_0 \implies i_1 \implies b \\
\end{split}
$$

($$ i_n $$ is the interpolant)

This simplifies complex relationships.

## Examples in the Real World 

1. My program (initial state) has a memory leak (final state). I need to 
   debug (find interpolants) in order to determine why I have a memory 
   leak.

## Craig Interpolation 

Given $$ L(I) = L(A) \intersect L(B) $$, if $$ A \implies B $$ is valid,
then there exists a formula $$ I $$ such that 

$$
A \implies I \and I \implies B
$$

Any symbol $$ I $$ must occur in _both_ $$ A $$ and $$ B $$.

The interpolant $$ I $$ gives use a _modular proof_ of $$ A \implies B $$,
due to the transitivity of implication.

Hypotherical Syllogism 
: Big word, not defined 

### Example 

A: Model 
B: Safety 

We want to prove:

$$ 
A \implies \not B 
$$ 

If we can show that 

$$ 
A \implies I, I \implies \not B 
$$

Then we show that our safety property holds.

## Feasibility

Refutation system 
: find a violation of a safety property 

Feasible property 
: If an interpolant for $$ A \and B $$ can be derived in polynomial time.

## Model Checking 

We generalize our intial state, $$ R_i(x_0) $$, and then check that the 
new generalization entails the safety property and holds in all 
reachable states. 

$$ R_i $$ is a formula that holds in all reachable states and entails 
$$ P $$, our safety property.

$$ x_0 $$ is some state that is the first step. 

For $$ i = 0, 1, ... $$ and $$ k > 0 $$ we check sat of:

$$
\begin{split}
R_i [ x_0 ] \\
\and Tr [ x_0, x_1 \and ... \and Tr [ x_{k-1}, x_k ] \\
\and (\not P [ x_0 ] \or ... \or \not P [ x_k ] ) \\
\end{split}
$$

We start with $$ R_0 = I $$. If the previous equation is unsat, then 
we _generalize_ $$ R $$ by doing $$ R_{i + 1} := R_i \or Int $$, where 
$$ Int $$ is the interpolant.

$$
\begin{split}
R_i \and Tr \satisfies Int \and \\ 
Int \implies \not \left(
    \and Tr [ x_0, x_1 \and ... \and Tr [ x_{k-1}, x_k ] \\
    \and (\not P [ x_0 ] \or ... \or \not P [ x_k ] ) \\
\right)
\end{split}
$$

> Aside: Basically, $$ Int $$ does all the big worky here.
