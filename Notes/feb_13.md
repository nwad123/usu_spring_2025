# Logical Effort

## Logical Effort of a N-input NAND gate

First we will find $R_{NMOS}$ for the NMOS, which will be 
$$
R_{NMOS} = \frac{1}{k_n n}
$$
where $k_n$ is the size of the NMOS's and $n$ is the number of NMOS. For the PMOS 
you will have $R_{PMOS}$ will be $k_p$ (the size of the PMOS) as that is the 
worst case.

To make the resistance equivalent to that of the inverter, we will have $k_p = 2$,
and $k_n = n$. This way the resistance for the PMOS will be 2, and the resistance 
for the NMOS will be 1, equivalent to the ideal inverter.

Then solving for capacitance, you will have $c_p = 2$ and $c_n = n$. The for the 
logical effort you will have:
$$
g = \frac{ n + 2 }{ 3 }
$$

## Logical Effort of a N-input NOR gate

For the PMOS you want $k_p = 2n$ and $k_n = 1$, then you get that your logical 
effort is:
$$
g = \frac{ 2n + 1 }{ 3 }
$$

# Parasitic Delay 

$$
p = \frac{ R_i C_{pi} }{ R_{inv} C_{inv} }
$$

Finding the parasitic delay you need to size the gate to the inverter resistance 
as we did for logical effort, then you need to find $C_{pi}$.

$ C_{pi} $
: Parasitic drain capacitance of gate.

$ C_{inv} $
: Input capacitance of inverter.

When the resistances are sized equivalently, then $p$ becomes:

$$
p = \frac{ C_{pi} }{ C_{inv} }
$$

$ C_{pi} $ is calculated by summing all drain capacitances at the output of the 
gate. For a 2-input NAND gate, we have three drains connecting to the output 
(the drain of the two PMOS and the drain of the NMOS) and they are all sized to 
be 2, we have a $C_{pi}$ of 6.

## Parasitic Capacitance for N-input Gates 

NAND:

$$
C_{pi} = 2n (\text{pmos}) + n (\text{nmos}) = 3n 
$$

NOR: 

$$
C_{pi} = 2n (\text{pmos}) + n (\text{nmos}) = 3n 
$$


