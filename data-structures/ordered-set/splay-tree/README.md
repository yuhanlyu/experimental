## Binary search tree
[Splay tree](https://en.wikipedia.org/wiki/Splay_tree) is self-balancing binary search
tree. The operations of insertion and deletion can be done in amortized O(lg n) time.

This module includes two implementations: recursive and top-down.

## Benchmark
The top-down method seems faster than recursive method.
<pre>
-------------------------------------------------------------------------------------
Benchmark                                              Time           CPU Iterations
-------------------------------------------------------------------------------------
SplayTreeBenchmark/SplayTreeInsert/1024            98888 ns      98665 ns       7091
SplayTreeBenchmark/SplayTreeInsert/4096           515572 ns     511869 ns       1348
SplayTreeBenchmark/SplayTreeInsert/16384         3325926 ns    3325925 ns        211
SplayTreeBenchmark/SplayTreeInsert/65536        19334380 ns   19332830 ns         36
SplayTreeBenchmark/SplayTreeInsert/262144      142807557 ns  142804579 ns          6
SplayTreeBenchmark/SplayTreeInsert/1048576     976057328 ns  975951253 ns          1
SplayTreeBenchmark/SplayTreeInsertRec/1024        112051 ns     112074 ns       6223
SplayTreeBenchmark/SplayTreeInsertRec/4096        575794 ns     575806 ns       1181
SplayTreeBenchmark/SplayTreeInsertRec/16384      3629448 ns    3629483 ns        193
SplayTreeBenchmark/SplayTreeInsertRec/65536     20911716 ns   20911585 ns         33
SplayTreeBenchmark/SplayTreeInsertRec/262144   151760328 ns  151757638 ns          5
SplayTreeBenchmark/SplayTreeInsertRec/1048576 1014238210 ns 1014067191 ns          1
SplayTreeBenchmark/SplayTreeDelete/1024            78667 ns      78668 ns       8851
SplayTreeBenchmark/SplayTreeDelete/4096           407298 ns     407278 ns       1720
SplayTreeBenchmark/SplayTreeDelete/16384         2665397 ns    2665377 ns        262
SplayTreeBenchmark/SplayTreeDelete/65536        15562037 ns   15551437 ns         45
SplayTreeBenchmark/SplayTreeDelete/262144      114922865 ns  114919322 ns          6
SplayTreeBenchmark/SplayTreeDelete/1048576     934774451 ns  934612709 ns          1
SplayTreeBenchmark/SplayTreeDeleteRec/1024         92119 ns      92092 ns       7645
SplayTreeBenchmark/SplayTreeDeleteRec/4096        478497 ns     478475 ns       1433
SplayTreeBenchmark/SplayTreeDeleteRec/16384      3017202 ns    3017079 ns        235
SplayTreeBenchmark/SplayTreeDeleteRec/65536     17306668 ns   17306196 ns         41
SplayTreeBenchmark/SplayTreeDeleteRec/262144   124644757 ns  124638615 ns          6
SplayTreeBenchmark/SplayTreeDeleteRec/1048576  967739570 ns  967711591 ns          1
</pre>
