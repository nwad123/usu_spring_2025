# Pipelining, OoO, Speculation

_Refer to copious pipelining, OoO, and speculation knowledge contained in my brain_

# Brainiac vs. Speed Demon

"Brainiac Designs"
: Utilize OoO execution and very complex hardware to achieve performance

"Speed Demon" Designs
: Utilize a really good compiler to achieve high performance on simpler hardware

Most processors find a balance between these two. Utilizing a good compiler and
complex hardware together provide good results.

The difference between these two seems silly for general purpose hardware, but for
HPC the difference comes into play. For example, an OoO processor takes up more size
and power, so if you are making a HPC system, is it better to go with:

- Fewer, more complex processors? (Brainiac)
- More simpler processors? (Speed Demon)

The compiler doesn't really come into play too much I feel like, so I'm not sure
why that was included in the definition. I guess it's whether or not the compiler
can make sense of a simple processor with many cores. Basically, it just comes down
to use cases as well. Some questions you could ask:

- Can I split my work up into many simple threads? (may be good for Speed Demon)
- Do I have a really complex code path for each thread that is not easily predictable?
  (May be good for Brainiac)

You could probably classify CPUs as _brainiacs_, and GPUs as _speed demons_.

# Simultaneous Multi-threading / Hyper-threading

Share two threads for the same program on the same core. Duplicate logical units
of a core (PC, ALU, registers) but share caches and other global data.

# Flynn's Taxonomy, SIMD, Vector / Tensor Processors

The idea is that you can do operations on _vectors_ of values, rather than _scalars_.

Flynn's Taxonomy
: Classifies SIMD, MIMD, SISD, etc, google it for more information.

## Memory Access and Scatter / Gather Algorithms

Data values may be stored across memory, scatter and gather algorithms pull them into
a contiguous array for easy vector operations.

# GPUs

Shader Functions
: Programmable stages of a GPU pipeline that uses points, lines, and triangles to draw
a surface.

Typically, GPUs are classified as _SIMD_ devices.

# NUMA vs. UMA

Uniform Memory Acess (UMA)
: Each processor can access the same memory at the same time.

Non-Uniform Memory Access (NUMA)
: Each processor may take a different amount of time to access the same memory as other
processors.

Basically, UMA is when processors are all on the same chip and connected to a contiguous
memory stick. NUMA is when processors may be on different chips, in different locations,
connected to a disjoint memory stick.

# Distributed Systems

Clusters
: A collection of commodity systems connected by commodity networking

Nodes
: Individual computation units on the cluster network

# Cache Coherence

For reference, there are several options for this, see ECE 5750 notes on:

- Snooping coherence
- Directory coherence

# Interconnects

Different topologies for an interconnect network lead to different considerations
and constraints. Again, just remember networking class.
