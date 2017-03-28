# Stackless quicksort
Traditional quicksort needs a stack either implicitly using recursion, or
explicitly maintaining the stack. But there is a way to implement quick-sort
in-place. The algorithm is from Lutz Michael Wegner's paper  
A generalized, one-way, stackless quicksort,  
BIT Numerical Mathematics 1987, Volume 27, Issue 1, pp 44-48  

## Behcnmark
I compare the stackless quicksort with STL sort, stable\_sort, and
stdlib's qsort.
---------------------------------------------------------------------
Benchmark                              Time           CPU Iterations
---------------------------------------------------------------------
QSortBenchmark/StacklessQSort   17665304 ns   17665085 ns        792
QSortBenchmark/STLQSort         14492520 ns   14492310 ns        966
QSortBenchmark/STLStableSort    11215687 ns   11215560 ns       1248
QSortBenchmark/QSort            26265846 ns   26265452 ns        533
