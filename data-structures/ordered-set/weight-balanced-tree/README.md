## Weight-balanced tree
[Weight-balanced tree](https://en.wikipedia.org/wiki/Weight-balanced_tree) is
self-balancing binary search tree. The operations of insertion and deletion
can be done in O(lg n) time in worst case. Moreover, the weight-balanced tree
maintains the subtree size in each node so that rank query can be supported
without storing any additional information. The amortized cost is O(1).

Although original weight-balanced tree can be tuned by specifying different
balance parameters, the invariants maintained in this implementation is
3 * size(subtree) >= size(sibling), which is the only feasible integer
parameter proved in the following papaer  

Yoichi Hirai, Kazuhiko Yamamoto  
[Balancing weight-balanced trees](https://doi.org/10.1017/S0956796811000104).

## Benchmark
This module contains three implementations:
* Insert/Delete: ordinary implementation, all cases are implementated as a  
separated function.
* InsertTemplate/DeleteTemplate: use C++ template mechanism to reduce code  
length by exploiting the symmetry of cases.
* InsertMacro/DeleteMacro: use macro to reduce code length by exploiting the  
symmetry of cases.

<pre>
----------------------------------------------------------------------
Benchmark                               Time           CPU Iterations
----------------------------------------------------------------------
WBTBenchmark/WBTInsert/1024         63266 ns      63268 ns      10903
WBTBenchmark/WBTInsert/4096        312897 ns     312897 ns       2250
WBTBenchmark/WBTInsert/16384      1961589 ns    1961532 ns        355
WBTBenchmark/WBTInsert/65536     11324838 ns   11324909 ns         61
WBTBenchmark/WBTInsert/262144    80174599 ns   80170161 ns         10
WBTBenchmark/WBTInsert/1048576  571112625 ns  571107180 ns          1

----------------------------------------------------------------------
Benchmark                               Time           CPU Iterations
----------------------------------------------------------------------
WBTBenchmark/WBTDelete/1024         47585 ns      47585 ns      14754
WBTBenchmark/WBTDelete/4096        244020 ns     244004 ns       2864
WBTBenchmark/WBTDelete/16384      1563659 ns    1563595 ns        448
WBTBenchmark/WBTDelete/65536      9257967 ns    9257659 ns         77
WBTBenchmark/WBTDelete/262144    63169563 ns   63155189 ns         12
WBTBenchmark/WBTDelete/1048576  531399663 ns  531214655 ns          2
</pre>
