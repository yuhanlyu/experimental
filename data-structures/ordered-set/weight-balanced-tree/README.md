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
<pre>
----------------------------------------------------------------------
Benchmark                               Time           CPU Iterations
----------------------------------------------------------------------
WBTBenchmark/WBTInsert/1024         83324 ns      83347 ns       8466
WBTBenchmark/WBTInsert/4096        401184 ns     401209 ns       1747
WBTBenchmark/WBTInsert/16384      2229145 ns    2229250 ns        314
WBTBenchmark/WBTInsert/65536     12291715 ns   12292429 ns         57
WBTBenchmark/WBTInsert/262144    85376775 ns   85379371 ns         10
WBTBenchmark/WBTInsert/1048576  577714688 ns  577730388 ns          1
WBTBenchmark/WBTDelete/1024         75146 ns      75170 ns       9288
WBTBenchmark/WBTDelete/4096        434004 ns     434027 ns       1613
WBTBenchmark/WBTDelete/16384      2552640 ns    2552692 ns        275
WBTBenchmark/WBTDelete/65536     16476430 ns   16476723 ns         43
WBTBenchmark/WBTDelete/262144   100884499 ns  100887368 ns          7
WBTBenchmark/WBTDelete/1048576  580354476 ns  580369904 ns          1
</pre>
