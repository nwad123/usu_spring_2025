# DC Characteristic Curve Regions for MOS Inverter

| Region |    NMOS    |    PMOS    |
| :----: | :--------: | :--------: |
|   A    |   Cutoff   |   Linear   |
|   B    | Saturation |   Linear   |
|   C    | Saturation | Saturation |
|   D    |   Linear   | Saturation |
|   E    |   Linear   |   Cutoff   |

_When deriving by hand remember that most values for PMOS are negative_

High skew and low skew gates are good for reset signals or signals where you might 
want one action to happen fast, and you don't care if a following action is 
slow.

# Noise Margins

Noise 
: When the voltage level is not at 1.0 or 0.0 exactly. For example, a voltage level 
  of 0.995 (when you are expecting 1.0) has a noise of 0.005.

Noise can be introduced by cross talk, parasitic capacitance, temperature, etc.

Noise is typically annotated as an acceptable range of voltages:

```
+-----------+ Vdd
|xxxxxxxxxxx|
|xxxxxxxxxxx| <-- Acceptable range of "Vdd", e.g. 1
|           |
|           | <-- Forbidden region (indeterminant state)
|           |
|xxxxxxxxxxx| <-- Acceptable range of "Gnd", e.g. 0
|xxxxxxxxxxx|
+-----------+ Gnd
```

This relates to the DC Characteristic Curve for Mos inverters by saying that the 
acceptable ranges are zones A, B, D, and E (with B and D being a little shaky) and 
zone C being forbidden.

## Noise in an Inverter 

```
    Input                 Output
+-----------+ Vdd     +-----------+ Vdd
|xxxxxxxxxxx|         |xxxxxxxxxxx|
|xxxxxxxxxxx|         |           |
|           |         |           |
|           |         |           |
|           |         |           |
|xxxxxxxxxxx|         |           |
|xxxxxxxxxxx|         |xxxxxxxxxxx|
+-----------+ Gnd     +-----------+ Gnd
```

Inverters are actually really reslient to noise, and when given a noisy signal they 
actually produce a less noisy signal. The diagram above shows an example of an input 
voltage range to an inverter and the corresponding output range. We can see from the 
diagram that  the output range is more constrained than the input range.

The reason for this is the map of the DC characteristic curve. Since it is close to an 
ideal approximation of `if vin < 0.5 then vout = 1 else vout = 0`, it is good at 
reducing the noise in a system. I guess you could say that the ouputs of sequential 
inverters _converges_ to either 1 or 0.

## More detail on noise ranges 

```
+-----------+ Vdd
|xxxxxxxxxxx|
|xxxxxxxxxxx| <-- Vih / Voh
|           |
|           |
|           |
|xxxxxxxxxxx| <-- Vil / Vol
|xxxxxxxxxxx|
+-----------+ Gnd
```

Vil 
: Maximum _low_ input voltage 

Vih 
: Minimum _high_ input voltage

Vol & Voh 
: Same as Vil and Vih for output voltages

Noise Margin (NM)
: The noise margin is the difference between the input and output margins.

$$ NM_{low} = V_{il} - V_{ol} $$

$$ NM_{high} = V_{oh} - V_{ih} $$

The goal is to have large noise margins so that a gate has better noise resilience. If 
the characteristic curve of an inverter is sharper it will generally shrink the 
forbidden region.

## Choosing the Bounds for the Forbidden Region 

We chose $ V_{in} $ and $ V_{out} $ where the slope for the characteristic curve 
$= \pm 1$ for a conservative estimate. The forbidden region is then inbetween 
Vih and Vol.

Forbidden Region 
: The region where the output of the gate is indeterminant based on the input
: AKA unstable region

