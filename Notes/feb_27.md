# Max Timing

## Two-phase Latch Timing

Three latches, L1, L2, and L3 with comb logic inbetween L1-L2, and L2-L3.

L1 and L3 get clock 1, and L2 gets clock 2. Clock 1 and clock 2 are out of 
phase.

The propogation delay of all the latches and comb logic of the sytem must be 
less than that the total cycle time of the clock.

When Clock 1 and Clock 2 are both 0, this is called the _non overlap_ region.

As a simplification, if the $t_{pdf}$ from the comb logic are equivalent and  
the $t_{pdq}$ for each latch is the same we can simplify the equation to 

$$
t_{pd} \le T - 2 \cdot t_{pdq}
$$

# Min-time Violation

What is the _smallest delay_ that the circuit can have?

## Flip Flop

We look at the $t_{ccq}$ (clock to Q) delay (the earliest time that a change is 
seen on the output Q of the FF. Then we track the time $t_{cd}$ from the $t_{ccq}$ 
of Q to D (being the first time when the output D2 from comb is changing).

If the values of the comb logic (D2) change before $t_{hold}$ of FF2 is done, then 
we experience a race condition and FF2 latches new data, effectively allowing data 
to pass two pipeline stages in one cycle.

$$
t_{hold} \le t_{ccq} + t_{cd} 
$$

## Issues in industry

Industry has a hard time detecting min-time errors. There are techniques to detect 
_max_ time errors (see RAZOR papers). RAZOR provides a dynamic technique, but it makes 
place and route hard, power becomes expensive, you have to add lots of stuff, etc.

## Two-phase Latch Circuit 

$$
t_{hold} \le t_{nonoverlap} + t_{ccq} + t_{cd}
$$

## Fixing Min-time Violation 

Buffer inversion adds buffers to min paths. This increases power usage, but fixes these 
issues.

# Time Borrowing 

Can you take time from one circuit and give it to another circuit in order to meet timing 
constraints together? This is used in Latch-based systems.

## 2-phase latches max time borrowing 

$$
T_C / 2 + t_{borrow} + t_{setup} + t_{nonoverlap} \le T_c 
$$

We can then derive the max borrow time from this this circuit.

## Flip Flops Time Borrowing 

If you need to do time borrowing for FFs, you can buffer the clock into some flip flops in 
order to cause the flip flops to trigger out of sync.

Clock skew also naturally happens as well for elements that are far from the original clk 
source.
