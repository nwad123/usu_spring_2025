# SAT Solvers 

## A quick review of chapter 9

Boolean Satifiability (SAT) 
: Determining whether there exists a varible assignment such that a given boolean formula 
evaluates to _true_.
: A proven NP-complete problem 

David-Logemann-Loveland (DPLL) Algorithm 
: An efficient algorithm for a _complete_ SAT solver (one that returns yes or no)

Conflict Driven Clause Learning (CDCL) Algorithms 
: Another algorithmic approach to SAT solving

## Chapter 10

Bounded Model Checking (BMC)
: A transistion system and a property are jointly unwound for a given number _k_ of 
steps to obtain a formula that that is satisfiable if there is a counterexample. 

In it's simplest form, BMC is _incomplete_ because bugs or errors that occur after _k_
transistions will be missed.

Kripke Structures
: A finite set of states, $S$, a set of initial states $I$, and a transition relations 
$T \subset S \times S$.

Kripke Path 
: A possibly inifinite sequence of states $s_0, s_1, ...$ such that $s_0$ is an initial 
state in $I$ and there is a transistion between any $s_i$ and $s_{i+1}$ in $T$.

The idea of BMC is to construct a formula that is _satisfied_ if there exists a _path_ 
that violates a given property.

### Safety Properties (10.2.2)

If $p$ is a global invariant we'll use $\textbf{G} p$ to represent _globally $p$_. A 
counterexample for this invariant in a bounded check can be modelled by checking that 
there is a path with _k_ transistions that ends with a state satisfying $\not p$. 

### Liveness Properties (10.2.3)

If $p$ is a invariant that should eventually hold, we'll use $\textbf{F} p$ to represent 
that. Counterexamples to this invariant are always given by a finite path (the stem) 
followed by a finite loop. 

A counterexample for this type of property is a finite loop where an accepting state is 
never reached.

Other approaches:

- Liveness to Safety translation: manipulate a model to change liveness property into a 
  safety property.
- _k_-Liveness: Didn't really understand, section 10.2.3.2

### BMC for Hardware (10.3)

HDLs typically have _simulation semantics_ and _synthesis semantics_.

#### BMC on net-lists (synthesis semantics):

Net-list 
: A directected graph of AND, NOT, REG, and INPUT nodes. Cycles must contain at least 
one REG node.

#### BMC on Software

1. Add a program counter 
2. Turn each instruction into transistion relations 

Optimizations:

- Merge all instructions within one basic block to a big single step using SSA 
- Path-based encodings perform forward symbolic execution along-side specific program 
  paths up to a given depth.

#### BMC for Multi-Threaded Programs **See chapter 18**

Path formulas with thread interleavings are built.

