# Delay Models

See slides from last time for the delay model. These models are much easier to reason about 
and derive than SPICE simulation.

## 5-input NAND Gate

In this circuit the pulldown network has five NMOS in series, and in the pullup network the 
gate has 5 PMOS in parallel. Imagine we have a load capacitance on the output, and we also 
have parasitic capacitance on each of the of the NMOS.

If the gate starts with a HIGH output, and then we turn the output to OFF, each of the NMOS 
will turn on.

Modelling the network will look like a resistance for each MOS, along with a capacitance 
for each NMOS as well.

Our fall delay will be equal to:

$$ 
t_{pdf} = R_5 (C_5 + ... + C_1 + C_L) + R_4 (C_4 + ... + C_1 + C_L) + ... + R_1 (C_1 + C_L)
$$

What happens if we reduce the size of N1 (the topmost NMOS in the series)? R1 will 
increase and C1 will decrease. Therefore if we shrink it then the overall time to 
go down will shrink as well.

Same happens if we grow the width of N5 (the lowest NMOS in the series, touching 
ground)

## Graded transistor sizing 

For large series networks we can size the _width_ of the NMOS as follows to optimize 
the delay:

$$
N_1 < N_2 < N_3 < N_4 < N_5 < ... < N_n
$$

This sizing reduces the delay as much as possible when using the simplified model. When 
using a SPICE simulation we will see a decrease in delay, but perhaps not the same as the 
simplified RC model.

## Estimate the Delay of a "Fanout-of-1" Inverter

It will be 6RC, see slides for example.

## Logical Effort Method of Delay Calculation

A technique used by engineers and designers to answer questions like, "What is the best 
circuit topology for a problem?" It allows for back of the envelope questions and make 
rapid comparisons between alternatives.

Unit Inverter 
: An inverter that has the size of 2 PMOS and size of 1 NMOS. Unit resistance of R and 
capacitance of 1C for NMOS and 2C for the PMOS.

We can calculate this by claculating $d_{unitless} \cdot \Tau$.

$$
d_{unitless} = gh + p 
$$

$g$ is called the logical effort. Comparison of the input capacitance to the capacitance of a 
unit inverter. If the capacitance of the gate is the same as a unit inverter, then this is a 
comparison of how the gate drives current.

$h$ is called the electrical effort. 

$p$ is called the parasitic delay.
