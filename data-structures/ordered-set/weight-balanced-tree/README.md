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

Ordinary implementation seems faster than other implementations.

<pre>
------------------------------------------------------------------------------
Benchmark                                       Time           CPU Iterations
------------------------------------------------------------------------------
WBTBenchmark/WBTInsert/1024                 79978 ns      79706 ns       8788
WBTBenchmark/WBTInsert/4096                381760 ns     381798 ns       1837
WBTBenchmark/WBTInsert/16384              2186649 ns    2183238 ns        324
WBTBenchmark/WBTInsert/65536             12085291 ns   12068219 ns         58
WBTBenchmark/WBTInsert/262144            83402499 ns   83240016 ns         10
WBTBenchmark/WBTInsert/1048576          566386180 ns  566404013 ns          1
WBTBenchmark/WBTDelete/1024                 73730 ns      73742 ns       9421
WBTBenchmark/WBTDelete/4096                424968 ns     424987 ns       1645
WBTBenchmark/WBTDelete/16384              2518844 ns    2518971 ns        279
WBTBenchmark/WBTDelete/65536             16143975 ns   16144579 ns         44
WBTBenchmark/WBTDelete/262144            99880838 ns   99885170 ns          7
WBTBenchmark/WBTDelete/1048576          569535171 ns  569555585 ns          1
WBTBenchmark/WBTInsertTemplate/1024         95449 ns      95492 ns       7353
WBTBenchmark/WBTInsertTemplate/4096        562032 ns     562190 ns       1289
WBTBenchmark/WBTInsertTemplate/16384      3069998 ns    3070369 ns        224
WBTBenchmark/WBTInsertTemplate/65536     20914682 ns   20915833 ns         33
WBTBenchmark/WBTInsertTemplate/262144   126250882 ns  126256677 ns          6
WBTBenchmark/WBTInsertTemplate/1048576  696301506 ns  696300011 ns          1
WBTBenchmark/WBTDeleteTemplate/1024         75504 ns      75526 ns       9249
WBTBenchmark/WBTDeleteTemplate/4096        433844 ns     433877 ns       1610
WBTBenchmark/WBTDeleteTemplate/16384      2553921 ns    2553995 ns        276
WBTBenchmark/WBTDeleteTemplate/65536     16325331 ns   16325996 ns         44
WBTBenchmark/WBTDeleteTemplate/262144    99717652 ns   99721441 ns          7
WBTBenchmark/WBTDeleteTemplate/1048576  572063007 ns  572086817 ns          1
WBTBenchmark/WBTInsertMacro/1024            94033 ns      94088 ns       7449
WBTBenchmark/WBTInsertMacro/4096           540904 ns     541058 ns       1253
WBTBenchmark/WBTInsertMacro/16384         3079201 ns    3079565 ns        223
WBTBenchmark/WBTInsertMacro/65536        21141152 ns   21142437 ns         32
WBTBenchmark/WBTInsertMacro/262144      126114211 ns  126119037 ns          5
WBTBenchmark/WBTInsertMacro/1048576     690795217 ns  690786190 ns          1
WBTBenchmark/WBTDeleteMacro/1024            73720 ns      73726 ns       9554
WBTBenchmark/WBTDeleteMacro/4096           426959 ns     426979 ns       1642
WBTBenchmark/WBTDeleteMacro/16384         2557933 ns    2557986 ns        278
WBTBenchmark/WBTDeleteMacro/65536        16176713 ns   16177322 ns         43
WBTBenchmark/WBTDeleteMacro/262144      100013756 ns  100017992 ns          7
WBTBenchmark/WBTDeleteMacro/1048576     574537764 ns  574554626 ns          1
</pre>
