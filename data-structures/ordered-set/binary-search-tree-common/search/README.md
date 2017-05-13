## Search in a binary search tree.
This module contains two implementations of search method.
* NaiveSearch: the ordinary version that uses three-way comparison.
* FastSearch: two-way comparison search methods proposed in the following
paper:  
Arne Andersson  
[A note on searching in a binary search tree](https://doi.org/10.1002/spe.4380211009)  


## Benchmark
The FastSearch method seems faster.

<pre>
------------------------------------------------------------------------------
Benchmark                                       Time           CPU Iterations
------------------------------------------------------------------------------
BSTSearchBenchmark/NaiveSearch/1024         12117 ns      12121 ns      58590
BSTSearchBenchmark/NaiveSearch/4096         94275 ns      94304 ns       7338
BSTSearchBenchmark/NaiveSearch/16384       725801 ns     726029 ns        972
BSTSearchBenchmark/NaiveSearch/65536      4432917 ns    4434267 ns        153
BSTSearchBenchmark/NaiveSearch/262144    30121293 ns   30129659 ns         23
BSTSearchBenchmark/NaiveSearch/1048576  288937435 ns  289012161 ns          2

-----------------------------------------------------------------------------
Benchmark                                      Time           CPU Iterations
-----------------------------------------------------------------------------
BSTSearchBenchmark/FastSearch/1024          9609 ns       9610 ns      72498
BSTSearchBenchmark/FastSearch/4096         69419 ns      69430 ns      10229
BSTSearchBenchmark/FastSearch/16384       616569 ns     616662 ns       1077
BSTSearchBenchmark/FastSearch/65536      4030621 ns    4030427 ns        168
BSTSearchBenchmark/FastSearch/262144    30765326 ns   30769753 ns         23
BSTSearchBenchmark/FastSearch/1048576  299793283 ns  299811571 ns          2

</pre>
