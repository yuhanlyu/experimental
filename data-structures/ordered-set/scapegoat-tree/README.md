## Binary search tree
[Scapegoat tree](https://en.wikipedia.org/wiki/Scapegoat_tree) is a
self-balancing binary search tree without storing any additional information
in each tree node.

## Benchmark
<pre>
--------------------------------------------------------------------------------------------
Benchmark                                                     Time           CPU Iterations
--------------------------------------------------------------------------------------------
ScapegoatBenchmark/ScapegoatTreeInsert/1024              253464 ns     253548 ns       2744
ScapegoatBenchmark/ScapegoatTreeInsert/4096             1079711 ns    1079820 ns        625
ScapegoatBenchmark/ScapegoatTreeInsert/16384            5538169 ns    5538453 ns        130
ScapegoatBenchmark/ScapegoatTreeInsert/65536           27460313 ns   27460542 ns         21
ScapegoatBenchmark/ScapegoatTreeInsert/262144         169645987 ns  169647567 ns          4
ScapegoatBenchmark/ScapegoatTreeInsert/1048576       1024736124 ns 1024746256 ns          1
ScapegoatRemoveBenchmark/ScapegoatTreeRemove/1024         83880 ns      83852 ns       8375
ScapegoatRemoveBenchmark/ScapegoatTreeRemove/4096        394545 ns     394424 ns       1770
ScapegoatRemoveBenchmark/ScapegoatTreeRemove/16384      2290931 ns    2290513 ns        302
ScapegoatRemoveBenchmark/ScapegoatTreeRemove/65536     13338966 ns   13336950 ns         53
ScapegoatRemoveBenchmark/ScapegoatTreeRemove/262144   109291292 ns  109287745 ns          6
ScapegoatRemoveBenchmark/ScapegoatTreeRemove/1048576  926407929 ns  926377088 ns          1
</pre>
