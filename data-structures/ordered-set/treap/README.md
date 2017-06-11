## Binary search tree
[Treap](https://en.wikipedia.org/wiki/Treap) is a randomized self-balancing
binary search tree. The operations of insertion and deletion can be done in
O(lg n) time in expectation.

The deletion can be done in top-down manner.

## Benchmark
<pre>
--------------------------------------------------------------------------
Benchmark                                   Time           CPU Iterations
--------------------------------------------------------------------------
TreapBenchmark/TreapInsert/1024        114061 ns     114077 ns       6208
TreapBenchmark/TreapInsert/4096        554205 ns     554242 ns       1269
TreapBenchmark/TreapInsert/16384      3239792 ns    3238065 ns        221
TreapBenchmark/TreapInsert/65536     16805687 ns   16805241 ns         42
TreapBenchmark/TreapInsert/262144   126441467 ns  126439121 ns          7
TreapBenchmark/TreapInsert/1048576  814749113 ns  814727095 ns          1
TreapBenchmark/TreapDelete/1024         71871 ns      71887 ns       9677
TreapBenchmark/TreapDelete/4096        457621 ns     457608 ns       1533
TreapBenchmark/TreapDelete/16384      2817241 ns    2817190 ns        244
TreapBenchmark/TreapDelete/65536     19070875 ns   19070515 ns         37
TreapBenchmark/TreapDelete/262144   124671002 ns  124668687 ns          6
TreapBenchmark/TreapDelete/1048576  722361880 ns  722343410 ns          1
</pre>
