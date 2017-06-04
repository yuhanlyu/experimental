## Binary search tree
[Splay tree](https://en.wikipedia.org/wiki/Splay_tree) is self-balancing binary search
tree. The operations of insertion and deletion can be done in amortized O(lg n) time.

This module includes two implementations: recursive and top-down.

## Benchmark
The top-down method seems faster than recursive method. Using sentinel seems
slower then using nullptr explicitly.
<pre>
-------------------------------------------------------------------------------------
Benchmark                                              Time           CPU Iterations
-------------------------------------------------------------------------------------
SplayTreeBenchmark/SplayTreeInsert/1024            94097 ns      94126 ns       7373
SplayTreeBenchmark/SplayTreeInsert/4096           496423 ns     496316 ns       1377
SplayTreeBenchmark/SplayTreeInsert/16384         3285079 ns    3284830 ns        214
SplayTreeBenchmark/SplayTreeInsert/65536        19213741 ns   19207866 ns         36
SplayTreeBenchmark/SplayTreeInsert/262144      136177582 ns  136150471 ns          6
SplayTreeBenchmark/SplayTreeInsert/1048576     935143694 ns  933583869 ns          1
SplayTreeBenchmark/SplayTreeInsertRec/1024        112431 ns     111888 ns       6251
SplayTreeBenchmark/SplayTreeInsertRec/4096        589273 ns     586004 ns       1183
SplayTreeBenchmark/SplayTreeInsertRec/16384      3687362 ns    3667400 ns        192
SplayTreeBenchmark/SplayTreeInsertRec/65536     21197935 ns   21082552 ns         33
SplayTreeBenchmark/SplayTreeInsertRec/262144   148803860 ns  147468528 ns          6
SplayTreeBenchmark/SplayTreeInsertRec/1048576  990132581 ns  981009913 ns          1
SplayTreeBenchmark/SplayTreeDelete/1024            75400 ns      75018 ns       9355
SplayTreeBenchmark/SplayTreeDelete/4096           392980 ns     392921 ns       1778
SplayTreeBenchmark/SplayTreeDelete/16384         2575904 ns    2570305 ns        273
SplayTreeBenchmark/SplayTreeDelete/65536        15221011 ns   15147093 ns         46
SplayTreeBenchmark/SplayTreeDelete/262144      113011104 ns  112843580 ns          7
SplayTreeBenchmark/SplayTreeDelete/1048576     901730198 ns  894575254 ns          1
SplayTreeBenchmark/SplayTreeDeleteRec/1024         91621 ns      91343 ns       7668
SplayTreeBenchmark/SplayTreeDeleteRec/4096        481730 ns     481558 ns       1457
SplayTreeBenchmark/SplayTreeDeleteRec/16384      2990165 ns    2989806 ns        235
SplayTreeBenchmark/SplayTreeDeleteRec/65536     17209123 ns   17148332 ns         41
SplayTreeBenchmark/SplayTreeDeleteRec/262144   123624504 ns  123289876 ns          6
SplayTreeBenchmark/SplayTreeDeleteRec/1048576  936155747 ns  931257564 ns          1
</pre>
