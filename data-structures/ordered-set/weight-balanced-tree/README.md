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
WBTBenchmark/WBTInsert/1024         78403 ns      78411 ns       8863
WBTBenchmark/WBTInsert/4096        368693 ns     368731 ns       1904
WBTBenchmark/WBTInsert/16384      2145944 ns    2146060 ns        326
WBTBenchmark/WBTInsert/65536     11903842 ns   11904446 ns         58
WBTBenchmark/WBTInsert/262144    77241870 ns   77245337 ns         10
WBTBenchmark/WBTInsert/1048576  544668097 ns  544691254 ns          1
WBTBenchmark/WBTDelete/1024         72338 ns      72345 ns       9610
WBTBenchmark/WBTDelete/4096        423205 ns     423205 ns       1660
WBTBenchmark/WBTDelete/16384      2439063 ns    2439157 ns        286
WBTBenchmark/WBTDelete/65536     15461887 ns   15462566 ns         45
WBTBenchmark/WBTDelete/262144    99484386 ns   99489832 ns          7
WBTBenchmark/WBTDelete/1048576  559750124 ns  559773981 ns          1
</pre>
