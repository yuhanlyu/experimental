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
WBTBenchmark/WBTInsert/1024         73295 ns      73307 ns       9436
WBTBenchmark/WBTInsert/4096        363342 ns     363320 ns       1946
WBTBenchmark/WBTInsert/16384      2166377 ns    2166230 ns        325
WBTBenchmark/WBTInsert/65536     11878268 ns   11876806 ns         59
WBTBenchmark/WBTInsert/262144    73615756 ns   73609235 ns         10
WBTBenchmark/WBTInsert/1048576  543782022 ns  543738739 ns          1

----------------------------------------------------------------------
Benchmark                               Time           CPU Iterations
----------------------------------------------------------------------
WBTBenchmark/WBTDelete/1024         61058 ns      61054 ns      11518
WBTBenchmark/WBTDelete/4096        311420 ns     311397 ns       2291
WBTBenchmark/WBTDelete/16384      1916533 ns    1916334 ns        369
WBTBenchmark/WBTDelete/65536     10835475 ns   10834715 ns         65
WBTBenchmark/WBTDelete/262144    65703348 ns   65698357 ns         11
WBTBenchmark/WBTDelete/1048576  506542678 ns  506508165 ns          1
</pre>
