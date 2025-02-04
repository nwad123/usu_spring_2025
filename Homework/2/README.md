# Histogram | Homework 2 CS 6300 | Nick Waddoups

The goal of this project was to write a _histogram generator_ that takes in a vector of 
floating point numbers and then generates a histogram data with a given number of bins 
containing the count of numbers in that range as well as the max value in the range.

For example:

Given input `[1, 2, 3, 4, 5]`, and directed to use two bins with ranges `(0,3], (3,6]`, 
return the following:

```
Counts: [Bin0: 3, Bin1: 2]
Maxes:  [Bin0: 3, Bin1: 5]
```

The output of this project was to be a command line program, `histogram`, that you could 
give the following command line arguments to to generate these bins. Datasets are to be 
randomly generated based on min/max measurements and the data count.

```sh
# Usage
./histogram <number of threads> <bin count> <min meas> <max meas> <data count>
```

A purpose of this program was to see the speedup that multithreading could produce, so I 
will implement three histogram generators:

- A serial histogram generator (single threaded),
- a global sum histogram generator (multi threaded),
- and a tree structed sum historgram generator (multi threaded).

## Prequisites for Building

- Unix-style system (for commands like `mkdir`)
- CMake 3.22 (or higher) installed
- C++20 / C++23 compliant compiler (tested on AppleClang 16)
- Python 3 
- Make

## Building 

1. Clone my `usu_spring_2025` repository.
2. Checkout the "hpc" branch.
3. Change into the "Homework/2" directory.
4. Type `make`

This will build three targets, `auto`, `cli`, and `test`.

- `auto`: This build generates the program I used to generate timing results for the plots. It 
  runs the Serial, Global, and Tree-structured histogram generators many times over a wide range 
  of datasizes and thread counts. NOTE: this program in it's current configuration took about 
  3 hrs and 20 minutes to run on my M3 MacBook pro with 18Gb RAM.

- `cli`: This build generates the command line histogram interface as specified above.

- `test`: This generates tests that ensure that each implementation is correctly calculating the 
  histogram data.

### Other Options 

There are several other targets in the Makefile that you can target. I won't exhaustively cover them 
here, but there are notes in the Makefile. The one I will cover is `make histogram`. This runs the 
build process and then symlinks `./build/cli` to `./histogram` for easy access to the command line  
application.

## Files 

- Plots/
    - Contains plots generated for the assignment.
- include/
    - Contains header files for the three histogram generators (called _solvers_ for some reason in 
      my code).
    - Contains other header files shared across the project.
- results/
    - Contains the output of `auto` as a `.csv`
- solvers/
    - Contains implementation details for each of the histogram generators (solvers).
- src/ 
    - Contains implementation details for shared source files (currently on the command line parser).
