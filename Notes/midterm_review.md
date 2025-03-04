# Elmore Delay of $n$-input NOR gate

1. Determine if rising or falling delay will be greater
2. Calculate resistance and capacitance for each PMOS as the rising edge 
   time will be greater.
3. Simplify equation to get the delay.

We can also calculate the falling delay by looking at the NMOS and the output 
delay. 

# Logical Effort Problem

1. Size the gates correctly. For a NOR gate the PMOS at sized at $$ \mu k $$
   and the NMOS are all $$ 1 $$. For the NAND gate the PMOS is sized at $$ \mu $$ and the 
   NMOS is sized at $$ k $$.

# Branching Effort Problem 

For a two-input NAND gate $$ g = \frac{ 4 }{ 3 } $$

1. Calculate $$ H $$, $$ G $$, and $$ B $$. Then calculate $$ F $$, then calculate $$ b $$.
2. See slide of lecture 11 
3. To find the sizing ratio determine the ideal, and then apply the same ratio of 
   $$ ideal : input capacitance $$ to $$ desired : calculated capacitance $$.
