# Predicate Abstraction Notes Day 4

See if we can prove that 15.7.1 is indeed the _strongest_ post condition, by comparing it to 
the method used to calculate the stronest post condition in the Dafny book.

Try to do the whole algorithm on the example code given. `AbstRefineLoop` seems to take in 
an empty set of predicates, so it is confusing what actually gets generated.

As a reminder for myself, to check termination we need to check that $ \psi_{ti} $ is 
_well-founded_ with relation to $ comp\# $, or in other words that if we repeatedly apply 
$ comp\# $ then $ \psi_{ti} $ will not grow forever and will eventually be closed under 
that operation.

## Teaching Comments 

The paper seems to give things a _bottom up_ manner. For example, they define `MakePath`, 
`FeasiblePath`, and `AbstReach` _before_ giving the definition of `AbstRefineLoop`. While 
this is a valid method, I think that sometimes it's easier to understand if you start from 
the high level goals (verify programs), and then delve into the details to support the 
general high level goals.

