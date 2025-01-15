# Chapter 15 - Predicate Abstraction for Program Verification

- Basic algorithms for the verification of safety and termination of programs
- Two underlying concepts are:
  1. Predicate abstraction, and
  2. Counterexample-guided Abstraction Refinement

## Introduction

Program Verification Algorithms
: Algorithms that take a program and a correctness property and try to answer the question
of whether the program is correct.

Safety
: Non-reachability of error states.

Termination
: Program does not take infinite time.

## Definitions

Program
: Specified through formulas and a set of logical variables, $V$

Program Counter (PC)
: A distinguished program variable of every program, $ pc \in V $

## Reachability

A state $s$ is reachable if there exists a program computation $ s_1, s_2, ... $ that contains
$s$.

A program is safe if error states are unreachable.

## Binary Reachability

Extending the notion of reachability from states to _pairs of states_. A pair of states, 
$ (s, s`) $ is reachable if there is an execution where $s$ followed by $s`$ is reachable.

## Correctness by Inductiveness


