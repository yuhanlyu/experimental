## Binary search tree
[Red-black tree](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree) is self-balancing binary search
tree. The operations of insertion and deletion can be done in O(lg n) time in
worst case.

This module implements two versions of insertion/deletion: iterative and recursive.

## Benchmark
<pre>
-------------------------------------------------------------------------------------
Benchmark                                              Time           CPU Iterations
-------------------------------------------------------------------------------------
RBTreeBenchmark/RBTreeInsert/1024                  82134 ns      82142 ns       8452
RBTreeBenchmark/RBTreeInsert/4096                 408462 ns     408470 ns       1714
RBTreeBenchmark/RBTreeInsert/16384               2388343 ns    2388370 ns        297
RBTreeBenchmark/RBTreeInsert/65536              12926194 ns   12924707 ns         54
RBTreeBenchmark/RBTreeInsert/262144             93262621 ns   93252196 ns          9
RBTreeBenchmark/RBTreeInsert/1048576           636186352 ns  636195278 ns          1
RBTreeBenchmark/RBTreeRecursiveInsert/1024         94966 ns      95005 ns       7390
RBTreeBenchmark/RBTreeRecursiveInsert/4096        454606 ns     454659 ns       1547
RBTreeBenchmark/RBTreeRecursiveInsert/16384      2568856 ns    2568896 ns        273
RBTreeBenchmark/RBTreeRecursiveInsert/65536     13899957 ns   13900449 ns         49
RBTreeBenchmark/RBTreeRecursiveInsert/262144    99517481 ns   99520146 ns          8
RBTreeBenchmark/RBTreeRecursiveInsert/1048576  682643912 ns  682658672 ns          1
RBTreeBenchmark/RBTreeDelete/1024                  94559 ns      94590 ns       7511
RBTreeBenchmark/RBTreeDelete/4096                 471931 ns     471958 ns       1472
RBTreeBenchmark/RBTreeDelete/16384               2672352 ns    2672068 ns        262
RBTreeBenchmark/RBTreeDelete/65536              14407905 ns   14407848 ns         48
RBTreeBenchmark/RBTreeDelete/262144             97566249 ns   97567471 ns          8
RBTreeBenchmark/RBTreeDelete/1048576           727517292 ns  727416291 ns          1
RBTreeBenchmark/RBTreeRecursiveDelete/1024         79770 ns      79784 ns       7840
RBTreeBenchmark/RBTreeRecursiveDelete/4096        380163 ns     380104 ns       1837
RBTreeBenchmark/RBTreeRecursiveDelete/16384      2324434 ns    2321493 ns        315
RBTreeBenchmark/RBTreeRecursiveDelete/65536     12345231 ns   12344732 ns         58
RBTreeBenchmark/RBTreeRecursiveDelete/262144    91259886 ns   91261810 ns          8
RBTreeBenchmark/RBTreeRecursiveDelete/1048576  680502090 ns  680516376 ns          1
</pre>
