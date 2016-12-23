# Advent Of Code 2016

This repository contains my solutions to the challanges posed at http://adventofcode.com/2016 and this README details the CPU run time of the code.

## Timing Analysis
### CPU Time per Task 

Python was timed in IPython 5.0.0 using the %timeit magic.

C was timed in the code using the clock function from the time.h header file and was compiled with gcc version 5.4.0

C++ code was complied with gcc version g++-5 gcc version 5.4.0 and was timed in the same manor as C.

Timing is done from the begining of the main function to the end.

### Day 1

|Language      | Part1    | Part 2           | 
|--------------|----------|------------------|
| Python 3.5.2 | 829 μs   |                  |
|    C         | 271 μs   | 452 μs           |
| C (with -O2) | 117 μs   | 142 μs           |   

### Day 2

|Language          | Part1    | Part 2           | 
|------------------|----------|------------------|
|    C++11         | 54 μs    | 102 μs           |
| C++11 (with -O2) | 26 μs    | 66 μs            |

### Day 3

|Language          | Part1    | Part 2           | 
|------------------|----------|------------------|
|    C++11         | 1.9 ms   |  4.6 ms          |
| C++11 (with -O2) | 1.5 ms   |  3.9 ms          |

### Day 4

|Language          | Part1    | Part 2           | 
|------------------|----------|------------------|
|    C++11         | 19 ms    |  20 ms           |
| C++11 (with -O2) | 10 ms    |  10 ms           |

### Day 5

|Language          | Part1    | Part 2           | 
|------------------|----------|------------------|
|    C++11         |  22.90 s |  22.65 s         |
| C++11 (with -O2) |  38.06 s |  33.87 s         |

### Day 6

