# DC Response for NMOS / PMOS

What is $ V_{out} $ vs $ V_{in} $ for an inverter?

For an ideal inverter, we say that you could represent it as a step curve, like so:

```
Vout = if Vin < 1 then 1 else 0
```

However, the realistic representation is a smoothed out version of this. This comes partially
because we represent the output as a capacitor that takes time to fill up to Vdd or time to
disperse to 0 when the inverter output is 0.

- PMOS are good pull-up transistors
- NMOS are good pull-down transistors

Another reason the real version cannot be a step function is because the _input_ is likely to
be an imperfect (smoothed) step function.

## NMOS Operation in an Inverter

|    Cutoff    |       Linear        |      Saturated       |
| :----------: | :-----------------: | :------------------: |
| $Vgsn < Vtn$ |    $Vgsn > Vtn$     |    $ Vgsn > Vtn$     |
|              | $Vdsn < Vgsn - Vtn$ | $ Vdsn > Vgsn - Vtn$ |

In an inverter circuit:

$$ Vgsn = Vin $$

$$ Vdsn = Vout $$

Then we can make replacements in the table above.

## PMOS Operation in an Inverter

|    Cutoff    |       Linear        |      Saturated       |
| :----------: | :-----------------: | :------------------: |
| $Vgsp > Vtp$ |    $Vgsp < Vtp$     |    $ Vgsp < Vtp$     |
|              | $Vdsp > Vgsp - Vtp$ | $ Vdsp < Vgsp - Vtp$ |

In an inverter circuit:

$$ Vgsp = Vin - Vdd \and Vgsp \le 0 $$

$$ Vdsp = Vout - Vdd \and Vdsp \le 0 $$

Then we can make replacements in the table above.

Then using the plots shown in the slides we can get the DC characteristic curve.

## DC Characteristic Curve Regions

_AKA DC transfer curve_

We can learn from this curve that voltages close to VDD / 2 create an _unstable_ output that
can oscillate, short, or be sadness overall.

Operating Regions

| Region |    NMOS    | PMOS |
| :----: | :--------: | :--: |
|   A    |   Cutoff   |      |
|   B    | Saturation |      |
|   C    | Saturation |      |
|   D    |            |      |
|   E    |            |      |
