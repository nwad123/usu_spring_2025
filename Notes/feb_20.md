# Exercise 

For an inverter 4 times a unit inverter:

- What is the input capacitance? 12 (8+4)
- What is the logical effort? 1
- What is the parasitic delay? 1

Slide 9, 10 from the slides for today cover all the equations we need for 
this homework assignment.

# Limits of Logical Effort 

Need path to computer G, can't know number of stages without G

Simplistic delay model, ignores input rise time effects

# Summary 

Logical effort is a "quick and dirty" emthod for talking about fast circuits,
but it's not a replacement for CAD tools.

# Static Timing Analysis

Critical Path 
: The maximum delay path.

Arrival Time (AT) 
: Worst-case delay of signal propogation from the inputs to the output of
the gate. AT is calculated topologically, from input to output.

Required Arrival Time (RT) 
: The latest time that signal _must_ arrive at the output of the gate. 
This is usually calcualted as part of a timing constraint, usually set 
by the desired clock speed. We can do a reverse topological calculation 
to see if we meet RT.

Slack
: Slack is calculated by RT - AT. If you have negative slack, the your 
worst-case arrival time is slower than your required arrival time.
