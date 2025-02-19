# Transition Systems

Transition System 
: Defined by a tuple, $ ( S, Act, \righrarrow, I, AP, L ) $ where 
    - $ S $ is a set of states 
    - $ Act $ is a set of actions 
    - $ \rightarrow $ is a transition relation
    - $ I $ is a set of initial states
    - $ AP $ is a set of atomic propositions 
    - $ L:S \implies 2^{} $ relates each state to a subset of the 
      atomic propositions.

A transistion system is _action-deterministic_ iff there is no more than 
1 successor state due to the same action.

A transition system is _AP-deterministic_ iff no more than 1 successor 
state with the same labeling.

## The Role of Non-Determinism 

- Used to model concurrency by interleaving 
- Used to model implementation freedom 
- Used to model _under-specified_ systems or _abstractions_ of real 
  systems.

# Executions 

An execution (run) is a linear sequence of state transitions. It can be 
finite or infinite.
