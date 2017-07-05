## Binary search tree
[Left-leaning red–black tree](https://en.wikipedia.org/wiki/Left-leaning_red%E2%80%93black_tree)
is self-balancing binary search tree. The operations of insertion and deletion
can be done in O(lg n) time in worst case.

The insertion is pretty easy, but the deletion is more complicated. Moreover,
since ther deletion requires rotation both on the way down and on the way up,
the deletion is very inefficient.

## Benchmark
<pre>
------------------------------------------------------------------------
Benchmark                                 Time           CPU Iterations
------------------------------------------------------------------------
LLRBBenchmark/LLRBInsert/1024        107101 ns     107099 ns       6533
LLRBBenchmark/LLRBInsert/4096        502648 ns     502596 ns       1368
LLRBBenchmark/LLRBInsert/16384      2886228 ns    2886314 ns        245
LLRBBenchmark/LLRBInsert/65536     15846060 ns   15846124 ns         44
LLRBBenchmark/LLRBInsert/262144    93516957 ns   93517580 ns          8
LLRBBenchmark/LLRBInsert/1048576  682735395 ns  682710742 ns          1
LLRBBenchmark/LLRBDelete/1024        171821 ns     171832 ns       4098
LLRBBenchmark/LLRBDelete/4096        929710 ns     929716 ns        740
LLRBBenchmark/LLRBDelete/16384      4900188 ns    4899449 ns        144
LLRBBenchmark/LLRBDelete/65536     27537429 ns   27538221 ns         26
LLRBBenchmark/LLRBDelete/262144   166353403 ns  166359505 ns          4
LLRBBenchmark/LLRBDelete/1048576  890177566 ns  890140579 ns          1
</pre>
