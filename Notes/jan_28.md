# Nonideal Transistor Theory

## ON and Off current 

$$ 
I_{on} = I_{ds} \text{ at } V_{gs} = V_{ds} = V_{DD}
$$

$$ 
I_{off} = I_{ds} \text{ at } V_{gs} = 0, V_{ds} = V_{DD}
$$

In cutoff, there is actually still a _very small_ current that passes through the 
transistor, even though the transistor is "off". This is called _leakage current_ 
and leads to _leakage power_ as well.

## Electric Fields 

There is a vertical electric field, $ E_{vert} $ that runs from the _gate_ to the 
_base_. There is also a horizontal field produces across the two `n+` terminals 
known as $ E_{lateral} $.

$$
E_{vert} = \frac{ V_{gs} }{ t_{ox} } 
$$

$$ 
E_{lateral} = \frac{ V_{ds} }{ L }
$$

## Velocity Saturation 

At high $ E_{lateral} $, carrier velocity rolls off. $ v_{carrier} = \mu E_{lateral} $
when $ E_{lateral} < E_{sat} $.

This has an effect on transistors that now their current is limited by velocity saturation.
We now say that the current is porportional to $ V_{DD}^\alpha $, where $ \alpha $ is 
empirically determined.

This means that as transistors get smaller ($ L $ approaches 0) velocity saturation gets 
worse, because $ E_{lateral} $ gets larger.

## Shockley Model 

This is the model we learned in the first few lectures, and it's a "first-order" model 
which is often used to represent a relatively ideal transistor. See [notes from Jan 14th](./jan_14.md)
for more.

## $ \alpha $ Power Model 

This is a simplified model that models the transistor as 100% linear in the linear region, 
and constant in the saturation region. The max current is proportional to $ V_{ds}^\alpha $.

## Channel Length Modulation

The depletion region around the drain grows which _shortens_ $ L $, which causes the current to 
grow slightly in saturation instead of remaining constant.

## Threshold Voltage 

This is the voltage that basically determines if the transistor is ON or OFF. For the transistor 
to be _ON_, then $ V_{gs} \ge V_{t} $, and vice versa for _OFF_.

The threshold is often suspected to be constant, but unfortunately it actually depends on basically 
everything else.

The leakage current is exponentially proportional to the threshold voltage, so if the threshold voltage 
shrinks, you get more leakage current, while if the threshold voltage grows, you get less leakage
current.

### Body Effect 

In NMOS, body is grounded, in PMOS, body is connected to $ V_{DD} $.

There is a voltage between the source and the body, $ V_{sb} $.

We can model the effect that $ V_{sb} $ has on $ V_t $ with the following equation:

$$
V_t = V_{t0} + \gamma ( \sqrt{ \phi_s + V_{sb} } - \sqrt{ \phi_s } ) 
$$

Where:

- $ \phi_s = 2 v_T l_n \frac{ NA }{ n_i } $ where $ v_T = \frac{ KT }{ q } $

When $ V_{sb} > 0 $, $ V_t $ increases. (Reverse body bias)

When $ V_{sb} < 0 $, $ V_t $ decreases. (Forward body bias)


