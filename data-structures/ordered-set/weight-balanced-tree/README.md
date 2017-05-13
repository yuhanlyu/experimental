## Binary search tree
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
------------------------------------------------------------------------------
Benchmark                                       Time           CPU Iterations
------------------------------------------------------------------------------
WBTBenchmark/WBTInsert/1024                 73568 ns      73583 ns       9510
WBTBenchmark/WBTInsert/4096                356699 ns     356698 ns       1968
WBTBenchmark/WBTInsert/16384              2100242 ns    2100201 ns        335
WBTBenchmark/WBTInsert/65536             11800622 ns   11800446 ns         60
WBTBenchmark/WBTInsert/262144            71791592 ns   71790262 ns         11
WBTBenchmark/WBTInsert/1048576          519808979 ns  519802815 ns          1
WBTBenchmark/WBTDelete/1024                 76352 ns      76357 ns       9377
WBTBenchmark/WBTDelete/4096                445833 ns     445823 ns       1547
WBTBenchmark/WBTDelete/16384              2538035 ns    2537974 ns        278
WBTBenchmark/WBTDelete/65536             15499869 ns   15499351 ns         45
WBTBenchmark/WBTDelete/262144            93927066 ns   93925907 ns          7
WBTBenchmark/WBTDelete/1048576          541448504 ns  541438544 ns          1
WBTBenchmark/WBTInsertTemplate/1024         95537 ns      95571 ns       7358
WBTBenchmark/WBTInsertTemplate/4096        568773 ns     568901 ns       1230
WBTBenchmark/WBTInsertTemplate/16384      3079906 ns    3080014 ns        224
WBTBenchmark/WBTInsertTemplate/65536     19723174 ns   19723068 ns         36
WBTBenchmark/WBTInsertTemplate/262144   119038112 ns  119036226 ns          6
WBTBenchmark/WBTInsertTemplate/1048576  659512120 ns  659504735 ns          1
WBTBenchmark/WBTDeleteTemplate/1024         76168 ns      76167 ns       9383
WBTBenchmark/WBTDeleteTemplate/4096        442752 ns     442739 ns       1581
WBTBenchmark/WBTDeleteTemplate/16384      2543859 ns    2543805 ns        279
WBTBenchmark/WBTDeleteTemplate/65536     15300608 ns   15300421 ns         46
WBTBenchmark/WBTDeleteTemplate/262144    94551831 ns   94550683 ns          7
WBTBenchmark/WBTDeleteTemplate/1048576  537135071 ns  537128465 ns          1
WBTBenchmark/WBTInsertMacro/1024            90380 ns      90408 ns       7654
WBTBenchmark/WBTInsertMacro/4096           524577 ns     524699 ns       1323
WBTBenchmark/WBTInsertMacro/16384         2975395 ns    2975498 ns        235
WBTBenchmark/WBTInsertMacro/65536        19012929 ns   19013059 ns         36
WBTBenchmark/WBTInsertMacro/262144      118872224 ns  118871260 ns          6
WBTBenchmark/WBTInsertMacro/1048576     655373472 ns  655360512 ns          1
WBTBenchmark/WBTDeleteMacro/1024            76331 ns      76337 ns       9387
WBTBenchmark/WBTDeleteMacro/4096           445878 ns     445876 ns       1565
WBTBenchmark/WBTDeleteMacro/16384         2541257 ns    2541205 ns        274
WBTBenchmark/WBTDeleteMacro/65536        15380672 ns   15380477 ns         46
WBTBenchmark/WBTDeleteMacro/262144       94698435 ns   94696620 ns          7
WBTBenchmark/WBTDeleteMacro/1048576     536769154 ns  536757685 ns          1
</pre>
