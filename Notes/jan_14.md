# Day 1

CMOS devices are not perfect switches, this class will explore the detailed
operation of CMOS transistors.

Make sure to bring pen / paper / ipad to class for writing 'n' stuff.

# MOS Devices

MOS
: Metal Oxide Semiconductor, a sandwhich of a metal layered on an oxide layered
on a semiconductor.

> Schematics
>
> NMOS has four terminals (cw starting at N): drain (d), base (b), source (s),
> gate (g)
>
> PMOS has four terminals (cw starting at N): source (s), base (b), drain (d),
> gate (g)

- Construction
  - Metal layer, usually poly-silicon, $Po Si$, forms the gate
  - Oxide layer, usually $S_i O_2$, acts as a dieletric
  - Semiconductor layer, usually doped silicon

```
           g
           |
+----------+------------+
| Metal PoSi            |
+-----------------------+
| Oxide SiO2            |
+-----------------------+
| P-type Semiconductor  |
|                       |
+----------+------------+
           |
           b
```

## Accumulation

$$ V_g < 0 $$

Holes in the P-type semiconductor move "up"

```
           g-------------------+
           |                   |
+----------+------------+      |
| Metal PoSi            |      |
+-----------------------+     (-)
| Oxide SiO2            |     Vg
+-----------------------+     (+)
| + + + + + + + + + + + |      |
| P-type Semiconductor  |      |
| - - - - - - - - - - - |      |
+----------+------------+      |
           |                   |
           b-------------------+
```

## Depletion

$$ 0 < V_g < V_t $$

"Upper" area of the semiconductor has no charge

```
           g-------------------+
           |                   |
+----------+------------+      |
| Metal PoSi            |      |
+-----------------------+     (+)
| Oxide SiO2            |     Vg
+-----------------------+     (-)
|                       |      |
| P-type Semiconductor  |      |
| + + + + + + + + + + + |      |
+----------+------------+      |
           |                   |
           b-------------------+
```

## Inversion

$$ V_t < V_g $$

"Upper" area of the semiconductor has a negative charge

```
           g-------------------+
           |                   |
+----------+------------+      |
| Metal PoSi            |      |
+-----------------------+     (+)
| Oxide SiO2            |     Vg
+-----------------------+     (-)
| - - - - - - - - - - - |      |
| P-type Semiconductor  |      |
| + + + + + + + + + + + |      |
+----------+------------+      |
           |                   |
           b-------------------+
```

# NMOS Devices

```
                     g
                     |
              +------+-------+
              |  Metal PoSi  |
      s       +--------------+       d
      |       |  Oxide SiO2  |       |
+-+---+---+---+--------------+---+---+---+-+
| |   n+  |                      |   n+  | |
| +-------+                      +-------+ |
|           P-type Semiconductor           |
+-------------------+----------------------+
                    |
                    b
```

1. Cutoff region, $V_gs < V_t$
   - In this region there are no carriers inbetween the two `n+` regions, so
     current cannot flow across the source and drain
2. Linear region, $V_t < V_gs$, current flows from drain to source if $V_ds > 0$
   - There are lots of carriers between the two `n+` regions, current flows
     proportional to $V_gs$
3. Saturation region $V_ds > V_gs - V_t$
   - Carriers are pushed out of the drain area, (when they are all pushed out that
     is called pinch off) and the NMOS acts as a current source where the output
     current is relatively constant, and does not change respective to $V_gs$

> How do we determine which is source and which is drain?
>
> NMOS, source is the majority carrier (electrons), so where the electrons go into
> the terminal is the source. Current goes from drain to source.
>
> PMOS, source is the majority carrier (holes), so where the holes go into the
> terminal is the source. Current goes from source to drain.

## Current in NMOS devices

Basically, in physics you can calculate charge as:

$$ I = \frac{dQ}{dt} $$

where $Q$ is charge and $t$ is time. Without calculus you can also use:

$$ I = \frac{Q}{t} $$

### Calculating the Charge $Q$

First we need to calculate the charge:

$$ Q = CV $$

Where $C$ is the capacitance, and $V$ is the voltage. The capacitance occurs between 
metal layer and the body layer, across the oxide layer.

$$ C = \frac{A \epsilon_{ox} }{d} = \frac{WL  \epsilon_{ox} }{t_{ox}} $$ 

Where $\epsilon_{ox}$ is the dielectric constant of the oxide, 
$A$, $W$, and $L$ refers to the area, width, and length of the gate,
and $d$ and $t_{ox}$ refers to the thickeness of the oxide.

$$ V = \frac{V_{gs} + V_{gd}}{2} - V_t $$

This is an average of the voltages across the device.

$$ Q = CV = WL \frac{ \epsilon_{ox} }{ t_{ox} } \left( V_{gs} - \frac{ V_ds }{ 2 } - V_t \right) $$

### Calculating the Time $t$

Now we have a calculation of a charge, and we can calculate the time it takes an 
electron to cross the channel. For that we'll calculate the velocity of an electron.

$$ v = \mu E $$

Where $\mu$ is the mobility of an electron, and $E$ is a field. Without a field, the 
electron will not move. The lateral field (from `n+` to `n+`), $E$, is determined by 
$V_{ds}$.

$$ E = \frac{ V_{ds} }{ L } $$

Where $L$ is the length of the channel.

$$ t = \frac{ L }{ v } = \frac{ L }{ \frac{ V_{ds} }{ L } } = \frac{ L^2 }{ \mu V_{ds} } $$

### Combining All The Parts

_This is known as the Shockley model_

$$ I_{ds} = \frac{ Q }{ t } = \mu \frac{\epsilon_{ox}}{t_{ox}} \frac{W}{L} ((V_{gs} - V_t)V_{ds} - \frac{V_{ds}^2}{2}) $$

All done, easy peasy.
