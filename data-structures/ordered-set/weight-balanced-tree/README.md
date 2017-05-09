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
WBTBenchmark/WBTInsert/1024         82329 ns      82040 ns       8413
WBTBenchmark/WBTInsert/4096        391438 ns     389372 ns       1794
WBTBenchmark/WBTInsert/16384      2224670 ns    2224692 ns        314
WBTBenchmark/WBTInsert/65536     12453130 ns   12453057 ns         57
WBTBenchmark/WBTInsert/262144    85428480 ns   84291242 ns         10
WBTBenchmark/WBTInsert/1048576  586864249 ns  578768978 ns          1
WBTBenchmark/WBTDelete/1024         77056 ns      76506 ns       9246
WBTBenchmark/WBTDelete/4096        443922 ns     439244 ns       1594
WBTBenchmark/WBTDelete/16384      2609844 ns    2594968 ns        268
WBTBenchmark/WBTDelete/65536     16765619 ns   16693783 ns         43
WBTBenchmark/WBTDelete/262144   103409444 ns  102769099 ns          7
WBTBenchmark/WBTDelete/1048576  586412888 ns  584390031 ns          1
</pre>
