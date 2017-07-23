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

------------------------------------------------------------------------------
Benchmark                                       Time           CPU Iterations
------------------------------------------------------------------------------
WBTBenchmark/WBTInsertTemplate/1024         76654 ns      76668 ns       9061
WBTBenchmark/WBTInsertTemplate/4096        361854 ns     361832 ns       1922
WBTBenchmark/WBTInsertTemplate/16384      2176727 ns    2176581 ns        319
WBTBenchmark/WBTInsertTemplate/65536     12361515 ns   12360540 ns         56
WBTBenchmark/WBTInsertTemplate/262144    76471641 ns   76466009 ns         10
WBTBenchmark/WBTInsertTemplate/1048576  561743381 ns  561701425 ns          1

---------------------------------------------------------------------------
Benchmark                                    Time           CPU Iterations
---------------------------------------------------------------------------
WBTBenchmark/WBTInsertMacro/1024         72609 ns      72617 ns       9518
WBTBenchmark/WBTInsertMacro/4096        346877 ns     346861 ns       2039
WBTBenchmark/WBTInsertMacro/16384      2091063 ns    2090932 ns        338
WBTBenchmark/WBTInsertMacro/65536     11763907 ns   11763017 ns         58
WBTBenchmark/WBTInsertMacro/262144    69662152 ns   69656972 ns         10
WBTBenchmark/WBTInsertMacro/1048576  521871706 ns  521833763 ns          1

----------------------------------------------------------------------
Benchmark                               Time           CPU Iterations
----------------------------------------------------------------------
WBTBenchmark/WBTDelete/1024         61058 ns      61054 ns      11518
WBTBenchmark/WBTDelete/4096        311420 ns     311397 ns       2291
WBTBenchmark/WBTDelete/16384      1916533 ns    1916334 ns        369
WBTBenchmark/WBTDelete/65536     10835475 ns   10834715 ns         65
WBTBenchmark/WBTDelete/262144    65703348 ns   65698357 ns         11
WBTBenchmark/WBTDelete/1048576  506542678 ns  506508165 ns          1

------------------------------------------------------------------------------
Benchmark                                       Time           CPU Iterations
------------------------------------------------------------------------------
WBTBenchmark/WBTDeleteTemplate/1024         61564 ns      61557 ns      11471
WBTBenchmark/WBTDeleteTemplate/4096        306246 ns     306225 ns       2328
WBTBenchmark/WBTDeleteTemplate/16384      1847573 ns    1847437 ns        381
WBTBenchmark/WBTDeleteTemplate/65536     10525370 ns   10524673 ns         62
WBTBenchmark/WBTDeleteTemplate/262144    61923990 ns   61919262 ns         12
WBTBenchmark/WBTDeleteTemplate/1048576  524983824 ns  524947602 ns          2

---------------------------------------------------------------------------
Benchmark                                    Time           CPU Iterations
---------------------------------------------------------------------------
WBTBenchmark/WBTDeleteMacro/1024         61102 ns      61097 ns      11531
WBTBenchmark/WBTDeleteMacro/4096        302223 ns     302196 ns       2331
WBTBenchmark/WBTDeleteMacro/16384      1848850 ns    1848671 ns        380
WBTBenchmark/WBTDeleteMacro/65536     10323358 ns   10322650 ns         67
WBTBenchmark/WBTDeleteMacro/262144    62380202 ns   62376277 ns         12
WBTBenchmark/WBTDeleteMacro/1048576  515080116 ns  515048557 ns          2

</pre>
