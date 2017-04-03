# Fibonacci numbers
This module contains four methods of generating Fibonacci numbers.
1. Iterative method.
1. Joseph Shortt
   [An Iterative Program to Calculate Fibonacci Numbers in O(log n) Arithmetic Operations](http://dx.doi.org/10.1016/0020-0190(78)90022-4).
k
1. L.F. Johnson
   [Tumble, a fast simple iteration algorithm for Fibonacci](https://doi.org/10.1016/j.ipl.2003.10.012).
1. [Q-Matrix](http://mathworld.wolfram.com/FibonacciQ-Matrix.html).

In the unit test, some arithmetics may overflow and may trigger undefined behavior.

## Benchmark

<pre>
----------------------------------------------------
Benchmark             Time           CPU Iterations
----------------------------------------------------
BM_Iterative         39 ns         39 ns   17952331
BM_Doubling          11 ns         11 ns   66511465
BM_Tumble            24 ns         24 ns   29845878
BM_QMatrix           15 ns         15 ns   47363973
</pre>
Doubling method is faster than Q-matrix method, 
and tumble method is faster than iterative method.
