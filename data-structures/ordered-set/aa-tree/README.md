## AA tree
[AA tree](https://en.wikipedia.org/wiki/AA_tree) is self-balancing binary search
tree. The operations of insertion and deletion can be done in O(lg n) time in
worst case.

## Benchmark
<pre>
----------------------------------------------------------------------------
Benchmark                                     Time           CPU Iterations
----------------------------------------------------------------------------
AATreeBenchmark/AATreeInsert/1024         88660 ns      88679 ns       7803
AATreeBenchmark/AATreeInsert/4096        431301 ns     431331 ns       1635
AATreeBenchmark/AATreeInsert/16384      2555073 ns    2555208 ns        272
AATreeBenchmark/AATreeInsert/65536     14335388 ns   14333761 ns         49
AATreeBenchmark/AATreeInsert/262144    89398424 ns   89402852 ns          8
AATreeBenchmark/AATreeInsert/1048576  690151465 ns  690178991 ns          1
AATreeBenchmark/AATreeDelete/1024         75397 ns      75391 ns       9050
AATreeBenchmark/AATreeDelete/4096        367752 ns     367748 ns       1908
AATreeBenchmark/AATreeDelete/16384      2274428 ns    2274506 ns        307
AATreeBenchmark/AATreeDelete/65536     13184052 ns   13184582 ns         53
AATreeBenchmark/AATreeDelete/262144    88123024 ns   88126462 ns          9
AATreeBenchmark/AATreeDelete/1048576  783856238 ns  783886474 ns          1
</pre>
