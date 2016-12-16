# Advent Of Code 2016

This repository contains my solutions to the challanges posed at http://adventofcode.com/2016 and this README details the CPU run time of the code.

## Timing Analysis
### CPU Time per Task 

Python was timed in IPython 5.0.0 using the %timeit magic.

C was timed in the code using the clock function from the time.h header file and was compiled with gcc version 5.4.0

C++ code was complied with gcc version g++-5 gcc version 5.4.0 and was timed in the same manor as C.

### Day 1

|Language      | Part1    | Part 2           | 
|--------------|----------|------------------|
| Python 3.5.2 | 829 μs   |                  |
|    C         | 16 μs    | 288 μs           |
| C (with -O2) | 16 μs    | 54 μs            |   

### Day 2

|Language          | Part1    | Part 2           | 
|------------------|----------|------------------|
|    C++11         | 29 μs    | 55  μs           |
| C++11 (with -O2) |  6 μs    | 34  μs           |

