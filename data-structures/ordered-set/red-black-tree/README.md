## Binary search tree
[Red-black tree](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree) is self-balancing binary search
tree. The operations of insertion and deletion can be done in O(lg n) time in
worst case.

This module implements two versions of insertion/deletion: iterative and recursive.

## Benchmark
<pre>
-------------------------------------------------------------------------
Benchmark                                  Time           CPU Iterations
-------------------------------------------------------------------------
RBTreeBenchmark/STLInsert/1024         83733 ns      83658 ns       8340
RBTreeBenchmark/STLInsert/4096        402189 ns     402221 ns       1761
RBTreeBenchmark/STLInsert/16384      2439218 ns    2439348 ns        291
RBTreeBenchmark/STLInsert/65536     12709457 ns   12709693 ns         54
RBTreeBenchmark/STLInsert/262144    98139093 ns   98139143 ns          8
RBTreeBenchmark/STLInsert/1048576  636878555 ns  636897639 ns          1

-------------------------------------------------------------------------
Benchmark                                  Time           CPU Iterations
-------------------------------------------------------------------------
RBTreeBenchmark/STLDelete/1024         76096 ns      76087 ns       9114
RBTreeBenchmark/STLDelete/4096        382458 ns     382469 ns       1824
RBTreeBenchmark/STLDelete/16384      2265118 ns    2264637 ns        309
RBTreeBenchmark/STLDelete/65536     11765114 ns   11765413 ns         57
RBTreeBenchmark/STLDelete/262144    90089191 ns   90092045 ns          8
RBTreeBenchmark/STLDelete/1048576  653176729 ns  653203141 ns          1

----------------------------------------------------------------------------
Benchmark                                     Time           CPU Iterations
----------------------------------------------------------------------------
RBTreeBenchmark/RBTreeInsert/1024         83766 ns      83794 ns       8064
RBTreeBenchmark/RBTreeInsert/4096        410029 ns     410069 ns       1689
RBTreeBenchmark/RBTreeInsert/16384      2324002 ns    2324126 ns        302
RBTreeBenchmark/RBTreeInsert/65536     12531097 ns   12531522 ns         56
RBTreeBenchmark/RBTreeInsert/262144    79088974 ns   79091816 ns         10
RBTreeBenchmark/RBTreeInsert/1048576  571777597 ns  571801036 ns          1

----------------------------------------------------------------------------
Benchmark                                     Time           CPU Iterations
----------------------------------------------------------------------------
RBTreeBenchmark/RBTreeDelete/1024         90926 ns      90902 ns       7620
RBTreeBenchmark/RBTreeDelete/4096        448920 ns     448815 ns       1552
RBTreeBenchmark/RBTreeDelete/16384      2585398 ns    2584648 ns        271
RBTreeBenchmark/RBTreeDelete/65536     14007307 ns   14002569 ns         51
RBTreeBenchmark/RBTreeDelete/262144    81264656 ns   81236282 ns          9
RBTreeBenchmark/RBTreeDelete/1048576  668728140 ns  668535596 ns          1

-------------------------------------------------------------------------------------
Benchmark                                              Time           CPU Iterations
-------------------------------------------------------------------------------------
RBTreeBenchmark/RBTreeRecursiveInsert/1024         94807 ns      94807 ns       7279
RBTreeBenchmark/RBTreeRecursiveInsert/4096        442719 ns     442633 ns       1575
RBTreeBenchmark/RBTreeRecursiveInsert/16384      2481125 ns    2480456 ns        277
RBTreeBenchmark/RBTreeRecursiveInsert/65536     13506362 ns   13493071 ns         49
RBTreeBenchmark/RBTreeRecursiveInsert/262144    84997039 ns   84875617 ns          9
RBTreeBenchmark/RBTreeRecursiveInsert/1048576  602780516 ns  601862254 ns          1

-------------------------------------------------------------------------------------
Benchmark                                              Time           CPU Iterations
-------------------------------------------------------------------------------------
RBTreeBenchmark/RBTreeRecursiveDelete/1024         74368 ns      74350 ns       9313
RBTreeBenchmark/RBTreeRecursiveDelete/4096        362304 ns     362226 ns       1913
RBTreeBenchmark/RBTreeRecursiveDelete/16384      2129844 ns    2129266 ns        333
RBTreeBenchmark/RBTreeRecursiveDelete/65536     11632385 ns   11630110 ns         60
RBTreeBenchmark/RBTreeRecursiveDelete/262144    71858017 ns   71844602 ns          9
RBTreeBenchmark/RBTreeRecursiveDelete/1048576  613010461 ns  612897498 ns          1
</pre>
