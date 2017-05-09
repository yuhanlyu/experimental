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
WBTBenchmark/WBTInsert/1024         82298 ns      81546 ns       8545
WBTBenchmark/WBTInsert/4096        388157 ns     386046 ns       1815
WBTBenchmark/WBTInsert/16384      2235231 ns    2235472 ns        315
WBTBenchmark/WBTInsert/65536     12449182 ns   12413894 ns         56
WBTBenchmark/WBTInsert/262144    85185498 ns   84993356 ns         10
WBTBenchmark/WBTInsert/1048576  587460463 ns  587498820 ns          1
WBTBenchmark/WBTDelete/1024         75817 ns      75290 ns       9227
WBTBenchmark/WBTDelete/4096        449998 ns     444627 ns       1588
WBTBenchmark/WBTDelete/16384      2601133 ns    2601317 ns        271
WBTBenchmark/WBTDelete/65536     16668906 ns   16563780 ns         42
WBTBenchmark/WBTDelete/262144   104218228 ns  103911254 ns          7
WBTBenchmark/WBTDelete/1048576  585950666 ns  585988729 ns          1
</pre>
