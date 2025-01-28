# Speedup and Effeciency of Parallel Programs

See slides for equations.

Ideal speed up would be directly proportional to the number of threads / processes used for the 
algorithm. However, both speedup and effeciency do not scale linearly according to the number 
of threads thrown at the program.

The more work that each thread has to do will improve effeciency. If each thread is only doing a 
little bit of work, then the cost of splitting up threads is not going to be amortized over the 
work that the thread is actually doing. Basically, if the thread is not doing enough work to 
"cancel out" the cost of using threads  and splitting up the work, you'll be less efficient.

_However_, even if you aren't maximally effecient, you will still get a good speedup.

> For example, if you throw 200 GPU cores at a problem and you only have an effeciency of 50%, 
> that still means that you will get a 100x speedup over using 1 core.

$$ 
T_{parallel} = T_{serial} / p + T_{overhead} 
$$

This represents the effect of overhead on the parallel execution.
