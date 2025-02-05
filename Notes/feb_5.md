# Abstraction Continued 

Note from last time I forgot to write down: The simulated model allows more _behaviors_ 
but has less states and transistions. This is because that the simulated model is more 
abstract and thus allows traces that the concrete model can't model.

## Existential Abstraction 

Concretization functions $\gamma$ can be generated using counter-examples like as 
shown in chapter 15 - predicate abstraction.

Weak Until $W$ 
: Holds for the same condition as _until_ ($U$) and additionally accepts the path 
where the predicate holds ever and the target state is never reached.
: See wikipedia page on LTL for more information on these

## Counter-example Guided Refinement 

Abstraction can generate spurious counter-examples that aren't actually present in 
the concrete model. An iterative loop of counter-example, refinement, etc. can produce 
the minimum viable model that can prove or disprove a property.

## Modal Simulation 

Introduces _may_ and _must_ transistion relations. 

May 
: For every concrete transistion there needs to be a corresponding _may_ transistion  

Must 
: For every _must_ transistion there needs to be a corresponding concrete transistion

_Check if we can apply definition 11 to Figure 8_

## Three-valued setting

We can now check $\phi$ _and_ $\not \phi$, which allows us to determine if a property holds,
does not hold, or is unknown. Counter-examples no longer get generated, but there is another 
system, TVAR, that can provide refinement on these "three-valued" models.
