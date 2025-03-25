# Dynamic Power

Today: how to optimize our dynamic power in a circuit.

$$
P_{dynamic} = P_{switching} + P_{short-circuit}
$$

## Switching Power Optimization

$$
P_{switching} = \alpha C V_{DD}^2 f
$$

Minimization goals:

- Activity factor ($$ \alpha $$)
  - Clock gating: turn off the clock to registers in unused blocks
  - You could set on/off blocks in the decode stage potentially
  - Decide which gate to use (see example below)
- Capacitance ($$ C $$)
  - Gate sizing / transistor sizing
  - Buffer insertion
- Supply voltage ($$ V_{DD} $$)
  - DVFS (Dynamic Voltage Frequency Scaling): run-time scaling of the clock 
    frequency and voltage.
  - Voltage domains: run sections of the circuit corresponding to different blocks
- Frequency ($$ f $$)

### Example: NAND vs. NOR

|              |             NAND              |                 NOR                 |
| :----------: | :---------------------------: | :---------------------------------: |
|  $$ P_1 $$   |       $$ 1 - P_A P_B $$       | $$ P_A \bar{P_B} + \bar{P_A} P_B $$ |
| $$ \alpha $$ | $$ P_A P_B - {(P_A P_B)}^2 $$ |          solve here later           |

### Example 2: Dynamic Power Party 

Design:

- 1 Billion transistors
- 50 millions logic 
  - Activity ($$ \alpha $$): 0.1
  - Average width: $$ 12 \lambda $$
- 950 million memory transistors
  - Activity factory: 0.02
  - Average width: $$ 4 \lambda $$
- 1.0 V 65 nm process, $$ \lambda = 25 \text{nm} $$
- $$ C = 1 \text{fF/\micro m} + 0.8 \text{fF/\micro m} $$

Solution:

$$
\begin{align*}
P_{dynamic} &= f V_{DD}^2 \sum_{i = 1}^n \alpha_i C_{Li} \\
\end{align*}
$$

## Level Converters

(See picture on phone of level converter)

# Static Power 

Next time?

# TODO

Look at _real_ reasons why newer ARM processors are better than Intel ones.

- SoC?
- ISA?
- Lower thresholds?
