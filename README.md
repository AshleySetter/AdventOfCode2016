# Advent Of Code 2016

This repository contains my solutions to the challanges posed at http://adventofcode.com/2016 and this README details the CPU run time of the code.

## Timing Analysis
### CPU Time per function call (the function completes the whole task)

### Day 1

Python was timed in IPython 5.0.0 using the %timeit magic.

C was timed in the code using the clock function from the time.h header file and was compiled with gcc version 5.4.0 20160609 (Ubuntu 5.4.0-6ubuntu1~16.04.4).

|Language      | Part1    | Part 2           | 
|--------------|----------|------------------|
| Python 3.5.2 | 829 μs   |                  |
|    C         | 16.4 μs  | 288 μs           |
| C (with -O3) |          |                  |

### Day 2

C++ code was complied with gcc version g++-5 (Homebrew gcc 5.3.0) 5.3.0

|Language          | Part1    | Part 2           | 
|------------------|----------|------------------|
|    C++11         |          |                  |
| C++11 (with -O3) |          |                  |