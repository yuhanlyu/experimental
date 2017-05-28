## Binary search tree
[AA tree](https://en.wikipedia.org/wiki/AA_tree) is self-balancing binary search
tree. The operations of insertion and deletion can be done in O(lg n) time in
worst case.

## Benchmark
<pre>
----------------------------------------------------------------------------
Benchmark                                     Time           CPU Iterations
----------------------------------------------------------------------------
AATreeBenchmark/AATreeInsert/1024         96629 ns      96621 ns       7210
AATreeBenchmark/AATreeInsert/4096        457547 ns     457529 ns       1530
AATreeBenchmark/AATreeInsert/16384      2645417 ns    2645300 ns        265
AATreeBenchmark/AATreeInsert/65536     14565404 ns   14564567 ns         48
AATreeBenchmark/AATreeInsert/262144    90446368 ns   90441236 ns          8
AATreeBenchmark/AATreeInsert/1048576  674931628 ns  674885912 ns          1
AATreeBenchmark/AATreeDelete/1024         73628 ns      73630 ns       9585
AATreeBenchmark/AATreeDelete/4096        432102 ns     432036 ns       1628
AATreeBenchmark/AATreeDelete/16384      2461026 ns    2460811 ns        285
AATreeBenchmark/AATreeDelete/65536     15021423 ns   15020325 ns         47
AATreeBenchmark/AATreeDelete/262144    94903779 ns   94898404 ns          7
AATreeBenchmark/AATreeDelete/1048576  577571170 ns  577539986 ns          1
</pre>
