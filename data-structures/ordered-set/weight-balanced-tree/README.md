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
WBTBenchmark/WBTInsert/1024                 81077 ns      81094 ns       8516
WBTBenchmark/WBTInsert/4096                380446 ns     380486 ns       1842
WBTBenchmark/WBTInsert/16384              2210276 ns    2210431 ns        318
WBTBenchmark/WBTInsert/65536             12479760 ns   12480180 ns         57
WBTBenchmark/WBTInsert/262144            87849126 ns   87848852 ns          9
WBTBenchmark/WBTInsert/1048576          608921807 ns  608915691 ns          1
WBTBenchmark/WBTDelete/1024                 80611 ns      80624 ns       8782
WBTBenchmark/WBTDelete/4096                456610 ns     456641 ns       1533
WBTBenchmark/WBTDelete/16384              2770414 ns    2770348 ns        254
WBTBenchmark/WBTDelete/65536             17725830 ns   17725765 ns         40
WBTBenchmark/WBTDelete/262144           109494499 ns  109493891 ns          6
WBTBenchmark/WBTDelete/1048576          618577935 ns  618571133 ns          1
WBTBenchmark/WBTInsertTemplate/1024        100121 ns     100165 ns       6946
WBTBenchmark/WBTInsertTemplate/4096        565160 ns     565285 ns       1231
WBTBenchmark/WBTInsertTemplate/16384      3412350 ns    3412698 ns        207
WBTBenchmark/WBTInsertTemplate/65536     23015936 ns   23016189 ns         31
WBTBenchmark/WBTInsertTemplate/262144   137637692 ns  137637030 ns          5
WBTBenchmark/WBTInsertTemplate/1048576  734915852 ns  734875425 ns          1
WBTBenchmark/WBTDeleteTemplate/1024         81077 ns      81086 ns       8699
WBTBenchmark/WBTDeleteTemplate/4096        459981 ns     459970 ns       1525
WBTBenchmark/WBTDeleteTemplate/16384      2752497 ns    2752425 ns        254
WBTBenchmark/WBTDeleteTemplate/65536     17735955 ns   17735570 ns         38
WBTBenchmark/WBTDeleteTemplate/262144   110334076 ns  110333094 ns          7
WBTBenchmark/WBTDeleteTemplate/1048576  626197913 ns  626201579 ns          1
WBTBenchmark/WBTInsertMacro/1024            96765 ns      96822 ns       7192
WBTBenchmark/WBTInsertMacro/4096           551068 ns     551208 ns       1272
WBTBenchmark/WBTInsertMacro/16384         3333989 ns    3334281 ns        213
WBTBenchmark/WBTInsertMacro/65536        22584893 ns   22585177 ns         31
WBTBenchmark/WBTInsertMacro/262144      134254057 ns  134253556 ns          5
WBTBenchmark/WBTInsertMacro/1048576     733587893 ns  733572320 ns          1
WBTBenchmark/WBTDeleteMacro/1024            79595 ns      79602 ns       8826
WBTBenchmark/WBTDeleteMacro/4096           455200 ns     455174 ns       1533
WBTBenchmark/WBTDeleteMacro/16384         2724934 ns    2724728 ns        254
WBTBenchmark/WBTDeleteMacro/65536        17717313 ns   17717062 ns         40
WBTBenchmark/WBTDeleteMacro/262144      109757553 ns  109757165 ns          6
WBTBenchmark/WBTDeleteMacro/1048576     613966219 ns  613963167 ns          1
</pre>
