# Linear I-V NMOS

As a review of last time (Shockley model): 

$$ I_{ds} = \frac{ Q }{ t } = \mu \frac{\epsilon_{ox}}{t_{ox}} \frac{W}{L} ((V_{gs} - V_t)V_{ds} - \frac{V_{ds}^2}{2}) $$

We can simplify $ \mu \frac{\epsilon_{ox}}{t_{ox}} \frac{W}{L} $ to be just $ \Beta $.

_Linear:_ 

$$ I_{ds} = \frac{ Q }{ t } = \Beta ((V_{gs} - V_t)V_{ds} - \frac{V_{ds}^2}{2}) $$

## Exercise 1

Substitute in $ V_{ds} = V_{gs} - V_t $, we can only supplant $ V_{ds} $ in for saturation.

$$ I_{ds} = \frac{ Q }{ t } = \Beta ((V_{gs} - V_t)(V_{gs} - V_t) - \frac{ {V_{gs} - V_t }^2 }{ 2 }) $$

$$ I_{ds} = \frac{ Q }{ t } = \Beta ((V_{gs} - V_t)(V_{gs} - V_t) - \frac{ (V_{gs} - V_t)(V_{gs} - V_t) }{ 2 }) $$

_Saturation:_ 

$$ I_{ds} = \frac{ Q }{ t } = \Beta ( \frac{ (V_{gs} - V_t)(V_{gs} - V_t) }{ 2 } ) $$

## All Equations 

1. Cutoff 
    
   $$ I = 0 $$ 

2. Linear 

   $$ I_{ds} = \frac{ Q }{ t } = \Beta ((V_{gs} - V_t)V_{ds} - \frac{V_{ds}^2}{2}) $$ 

3. Saturation 
    
$$ I_{ds} = \frac{ Q }{ t } = \Beta ( \frac{ (V_{gs} - V_t)(V_{gs} - V_t) }{ 2 } ) $$

## Example 

How do we draw the curve for a real process node?

Specification (AMI (ON) Semiconductor):

- $ t_{ox} = 100 \text{Angstroms} $
- $ \mu = 350 \text{cm}^2 / \text{Vs} $
- $ V_t = 0.7 \text{V} $ 
- $ V_{gs} = 0, 1, 2, 3, 4, 5 $
- $ V_{ds} = 0, 1, 2, 3, 4, 5 $
- $ W/L = 4/2 \lambda $
- $ \epsilon_{ox} = k_{ox} \epsilon_0 $ (where $ \epsilon_0 $ is the permittivity of free space)

Solve for $ \Beta $, substitute in voltages in the back half of the equation.

# PMOS 

Doped with `p+` instead of `n+`

```
                     g
                     |
              +------+-------+
              |  Metal PoSi  |
      d       +--------------+       s
      |       |  Oxide SiO2  |       |
+-+---+---+---+--------------+---+---+---+-+
| |   p+  |                      |   p+  | |
| +-------+                      +-------+ |
|           N-type Semiconductor           |
+-------------------+----------------------+
                    |
                    b
```

The source and drain switch places because the _majority carrier_ for the PMOS are the 
holes, as opposed to the electrons. We consider the holes to flow in the opposite 
direction of the electrons, so we switch the location of the drain and the source.

For PMOS:

- $I_ds$ is negative 
- $V_ds$ is also negative

Equations for _cutoff_, _linear_, and _saturation_ are the same as NMOS, while keeping in
mind the negative values for $I_ds$ and $V_ds$.

```
     PMOS Diagram
                  s
                  |
              +---+
            | |
g ---------O+ +----- b
            | |
              +---+
                  |
                  d
```

# Comparing NMOS and PMOS $I_ds$ plots.

_Holes_ are half as fast as electrons, so for everything else the same, the PMOS $I$ will be 
half the strength. That means to compensate for slower PMOS, we double the width of the NMOS
to make it slower as well. That way there isn't a mismatch.

# Capacitance in MOS

Capacitance takes _time_ to actually change (an _RC_ delay), so the capacitance in a MOS 
device defines the delay of every gate. It also determines the switching (dynamic) 
power of the circuit.

```
     NMOS Diagram
                  d
                  |
              +---+
            | |
g ----------+ +----- b
            | |
              +---+
                  |
                  s
```

Capacitances to consider:

- Oxide Related
  + Gate to body ($ C_{gb} $) 
  + Gate to source ($ C_{gs} $)
  + Gate to drain ($ C_{gd} $)

- Parasitic (Diffusion) happens across the 2 PN junctions
  + Drain to body ($ C_{db} $) 
  + Source to body ($ C_{sb} $)

In a chip design, you can't extract parasitic capacitance values until after layout is done. 
Synopsis and cadence tools can _extract_ the capacitance and then you can run simulations on 
it.

The capacitance is not a constant, it depends on the state of the MOS. There is a table of the 
capacitances in the _cutoff_, _linear_, and _saturation_ states.

|     | Cutoff | Linear | Saturation |
|:---:|:---:|:---:|:---:|
| $C_{gb}$ | $C_{ox}WL$ |0 |0 |
| $C_{gd}$ | $C_{ox}WL_{overlap}$ |$1/2 C_{ox}WL + C_{ox}WL_{overlap}$ | $C_{ox}WL_{overlap}$ |
| $C_{gs}$ | $C_{ox}WL_{overlap}$ |$1/2 C_{ox}WL + C_{ox}WL_{overlap}$ | $2/3 C_{ox}WL + C_{ox}WL_{overlap}$|

Pinchoff
: Always happens at the drain of the NMOS 

Gate to Source Capacitance at Pinchoff is approximated with a 2/3 as the channel is not parallel.

Table 8.5 in the book gives diffusion / parasitic capacitances.
