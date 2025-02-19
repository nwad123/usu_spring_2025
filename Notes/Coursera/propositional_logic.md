# Propositional Logic

Proposition
: A is a statement that evaluates to _true_ or _false_

Atomic Proposition 
: A proposition w/out any logical operators 

Compound Propositions 
: Atomic propositions combined with _NOT_, _AND_, or _OR_ operators.

Conjunction 
: The _AND_ operation 

Disjunction 
: The _OR_ operatation 

Negation 
: The _NOT_ operation

Logical Equivalent 
: Two propositions are logically equivalent iff they have _identical_ 
truth values for each possible truth assignment
: Denoted by the triple equal sign 

Conditional Proposition (Implies ->)
: A proposition where a conclusion is derived from a hypothesis

$\mu$
: An evaluation function that assigns a 1 or 0 to every atomic 
proposition.
: $ \mu : AP -> \{ 0, 1 \} $

# Predicate Logic 

Predicate Logic 
: An extension of propositional logic that is based on the composition 
of _predicates_

Predicate 
: A _sentence_ that contains a finite number of variables and becomes a 
proposition when specific values are substituted for the variables
: The domain of the predicate is the set of all values that may be 
substituted in place of the variable 

> Note: define sentence, even briefly

Quantification 
: The process that specifies the truth of the predicate with respect to 
the domains of the variables in the predicates 

Universal Quantifier (forall) 
: e.g. $ \forall x \in \nat, x \ge 0 $
: or in Dafny, ` forall x : int :: x > 0 => x*x > x `

Universal Statement 
: A statment of the form of $ \forall x \in Domain, Pred(x) $. This 
statement is true iff $ Pred(x) $ is true for _every_ $x$ in $Domain$.

Existential Quantifier (exists) 
: e.g. $ \exists $ 

Existential Statement 
: True iff $ Pred(x) $ is true for _least_ one variable.

Witness (of an existential proposition)
: A value $ x \in Domain $ such that $ Pred(x) $ is true.

# Set Theory 

Set 
: A collection of things called _elements_ or _members_ 

Set Builder Notation 
: $ \{ x \ in Set | Pred(x) \} $

Subset 
: A is a _subset_ of B iff every element in A is also in B 
: A _proper_ subset iff every element in A belongs to B, and there are 
elements in B that do not belong to A 

Equality 
: Two sets are equal if they have the same elements 

Operations 
- Intersection $ A \intersect B = \{ x \in U | x \in A \and x \in B \} $
- Union $ A \union B = \{ x \in U | x \in A \or x \in B \} $
- Difference $ A \difference B = \{ x \in U | x \in A \and x \notin B \} $
- Difference $ A \complement = \{ x \in U | x \notin A \} $

Power Set 
: $P(A)$ is the set of _all_ subsets of A
: Also defined as $ 2^A $

Cartesian Products 
: Mmmm refer to itertools for what this is. Math definition is too hard to 
write down :).
: Denoted by $ \times $

Binary Relation 
: A subset of $ A \times B $ where each ordered pair $ (a, b) $ is in $R$
: A is the _domain_ of R
: B is called the _co-domain_ of R
: Relation is written as 
$ \forall (x,y) \in A \times B, (x,y) \in R \iff xRy $

Properties of Relations 
- Reflexive $ \forall x \in A, xRx $
- Symmetric $ \forall x,y \in A, xRy \implies yRx $
- Anti-symmetric $ \forall x,y \in A, xRy \and yRx \implies x = y $
- Transitive $ \forall x,y,z \in A, xRy \and yRz \implies xRz $
## Sets and Logic 

With set builder notation we can use a _predicate_ to define a set based 
off another set, and using this we can actually apply logic to the sets 
without individually checking every element.

For example, to check if A is a subset of B, we might just check if 
every element in A is also in B, but what if there a lot (potentially 
infinite) elements? Instead, we could do some universal quantification 
like so:

$$
A = \{ x | P(x) \}, B = \{ x | Q(x) \}
$$

$$
A \subset B \iff \forall x, P(x) \implies Q(x) 
$$


