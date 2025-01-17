# Predicate Abstraction (in-class) 2

Remember introduction Coursera course is due Feb 5th. Add feedback to the google sheet and potentially 
write out more in depth ideas (evaluations, suggested improvements).

## Post Renaming and stuff

In 15.4.1 we don't really need to have an explicit rename step because of the introduction of the 
double prime variables. Just kidding, the actual process is that we do these steps:

1. Conjoin
2. Rename 
3. Existentially quantify 

> Research more about existential quantification

## Relational Composition Thinking

We have two transition relations, one goes from $R1 :: V \rightarrow V`$ and the other one also goes from 
$R2 :: V \rightarrow V`$. Uh oh! We need to rename our variables. We change this to be instead 
$R1 :: V \rightarrow V``$ and $R2 :: V`` \rightarrow V`$. $V``$ acts as a bridge between the two, so 
that $ R1 \circ R2  = V \rightarrow V`` \rightarrow V` $ 

> Do an example of reachability to make sure we are understanding it right

## Presenter notes

Being and HDMI adapter, as the classroom doesn't appear to have one.

