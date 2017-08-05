## AA tree
[AA tree](https://en.wikipedia.org/wiki/AA_tree) is self-balancing binary search
tree. The operations of insertion and deletion can be done in O(lg n) time in
worst case.

## Benchmark
<pre>
----------------------------------------------------------------------------
Benchmark                                     Time           CPU Iterations
----------------------------------------------------------------------------
AATreeBenchmark/AATreeInsert/1024         98516 ns      98544 ns       7063
AATreeBenchmark/AATreeInsert/4096        462199 ns     462213 ns       1518
AATreeBenchmark/AATreeInsert/16384      2688019 ns    2688070 ns        260
AATreeBenchmark/AATreeInsert/65536     14645814 ns   14645880 ns         47
AATreeBenchmark/AATreeInsert/262144    93200115 ns   93200366 ns          8
AATreeBenchmark/AATreeInsert/1048576  692331070 ns  692328198 ns          1
AATreeBenchmark/AATreeDelete/1024         84495 ns      84503 ns       8148
AATreeBenchmark/AATreeDelete/4096        415080 ns     415071 ns       1688
AATreeBenchmark/AATreeDelete/16384      2445725 ns    2444998 ns        287
AATreeBenchmark/AATreeDelete/65536     13583732 ns   13580556 ns         52
AATreeBenchmark/AATreeDelete/262144    87933682 ns   87899280 ns          8
AATreeBenchmark/AATreeDelete/1048576  756963568 ns  756740038 ns          1
</pre>
