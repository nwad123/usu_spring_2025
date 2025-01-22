# Predicate Abstraction Day 3

15.4 Termination of programs. Well-founded-ness means that if we iteratively grow $ \psi $,
the transition invariant, we will reach a state where it will not grow any further. In 
laymans terms, this means that when we calculate $ \psi_n $ it will not be an infinite 
sequence.

Well-founded Relation for Transition Invariant 
: Eventually there will be a $ \psi_{k+1} $ that is equivalent to $ \psi_{k} $.

Sometimes the procedure for checking a program does not terminate, even if the program 
itself terminates.
