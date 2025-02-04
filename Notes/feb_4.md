# Lab Notes

Standard Cell Library
: A library provided by a manufacturer that specifies power, timing, etc. for a set
of standard cell blocks.

## ASIC Design Methodology

1. High level design
2. RTL design
3. System, timing, and logic verification
   - Simulation, verification, etc.
4. Physical design
   - Covered in last semesters class
5. Performance and manufacturability verification
   - Extraction of physical view
   - Verifing of timing / signal integrity
   - Design rule checking (DRC)

# CMOS Delay

Timing optimizations at each level:

- Architecture:
  - Pipelining
  - Caches
  - Separate execution units
  - Operation / datatype / instruction set choice
  - Num execution units
- Logic (netlist and gates):
  - Boolean simplification
  - Broad circuit vs. deep circuit, number of stages, critical path
  - Size of gates (impacts capacitance and current levels)
- Circuit
  - Transistor sizing
  - CMOS styles (different combinations of nmos and pmos)
- Layout
  - Minimize wire length (routing)
  - Optimize cell placement
  - Reduce area (floor planning)

## CMOS Delay Definitions

$t_{pdr}$
: Propogation, Delay, _Rise_
: This is the delay that occurs from input to _rising_ output at $V_{dd} / 2$

$t_{pdf}$
: Propogation, Delay, _Fall_
: This is the delay that occurs from input to _falling_ output at $V_{dd} / 2$

> $t_{pdr}$ may be equal to $t_{pdf}$ if the transistors are sized to have equivalent
> power. However, if the transistors are not size-matched they will not be equal.

$t_{pd}$
: Average propogation delay $\frac{ t_{pdr} + t_{pdf} }{ 2 }$

$t_{r}$
: Rise time
: The time taken to rise from $0.2 V_{dd}$ to $0.8 V_{dd}$

$t_{f}$
: Fall time
: The time taken to fall from $0.8 V_{dd}$ to $0.2 V_{dd}$

Contamination delay happens when we have CMOS in parallel and they respond slightly 
differently.

$t_{cdr}$
: Rising Contamination Delay
: From input to rising output crossing $V_{dd} / 2$

$t_{cdf}$
: Falling Contamination Delay
: From input to falling output crossing $V_{dd} / 2$

$t_{cd}$
: Average contamination delay $\frac{ t_{cdr} + t_{cdf} }{ 2 }$

## Simulated CMOS Delays 

We could use SPICE to simulate these circuits, but those simulations may take a long time 
for large circuits, and may not be flexible for rapid iteration. Instead, we can notice 
that the output voltage usually looks similar to a _RC_ circuit waveform, so we can just 
model the transistor as an RC network.

Capacitances to consider:

- $C_{gb}$, gate to body 
- $C_{db}$, drain to body 
- $C_{sb}$, source to body

Capacitance $C$ is proportional to the size of the transistor, $k$, such that 
$ C_t \propto Ck $ for a transistor $t$

Resistances to consider:

- $R$, resistance between drain and source, proportional to $k$ (size of transistor) 
  such that $R_t \prop \frac{ R }{ k }$ for a transistor $t$

Also, there is a switch inbetween source and drain

For NMOS the capacitance is between the node and _ground_, but for PMOS the capacitance 
is between the node and _$V_{dd}$_, because of what each transistors body is connected to.

Also, PMOS have a factor of 2 in their equations because of the respective mobility of 
the majority carriers. The mobility of electrons is typically twice as fast as the holes.
