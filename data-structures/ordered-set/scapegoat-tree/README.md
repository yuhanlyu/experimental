## Scapegoat tree
[Scapegoat tree](https://en.wikipedia.org/wiki/Scapegoat_tree) is a
self-balancing binary search tree without storing any additional information
in each tree node. In this module, the rebalance is done by copy all elements
to an array and rebuild the tree. Thus, the rebalance requires O(n) additional
memory.

## Benchmark
<pre>
--------------------------------------------------------------------------------------
Benchmark                                               Time           CPU Iterations
--------------------------------------------------------------------------------------
ScapegoatBenchmark/ScapegoatTreeInsert/1024        239379 ns     239415 ns       2894
ScapegoatBenchmark/ScapegoatTreeInsert/4096       1039618 ns    1039698 ns        662
ScapegoatBenchmark/ScapegoatTreeInsert/16384      4969833 ns    4969980 ns        139
ScapegoatBenchmark/ScapegoatTreeInsert/65536     23637328 ns   23637636 ns         29
ScapegoatBenchmark/ScapegoatTreeInsert/262144   134152579 ns  134155854 ns          6
ScapegoatBenchmark/ScapegoatTreeInsert/1048576  796125741 ns  796139129 ns          1
ScapegoatBenchmark/ScapegoatTreeDelete/1024         77442 ns      77446 ns       9036
ScapegoatBenchmark/ScapegoatTreeDelete/4096        357997 ns     357991 ns       1966
ScapegoatBenchmark/ScapegoatTreeDelete/16384      2159288 ns    2159144 ns        325
ScapegoatBenchmark/ScapegoatTreeDelete/65536     11727373 ns   11727392 ns         60
ScapegoatBenchmark/ScapegoatTreeDelete/262144    83622994 ns   83551017 ns          9
ScapegoatBenchmark/ScapegoatTreeDelete/1048576  756575396 ns  756573682 ns          1
</pre>
