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
SplayTreeBenchmark/SplayTreeInsert/1024            91272 ns      91270 ns       7658
SplayTreeBenchmark/SplayTreeInsert/4096           485628 ns     485670 ns       1448
SplayTreeBenchmark/SplayTreeInsert/16384         3203175 ns    3203272 ns        218
SplayTreeBenchmark/SplayTreeInsert/65536        18648240 ns   18648602 ns         38
SplayTreeBenchmark/SplayTreeInsert/262144      114455251 ns  114441755 ns          7
SplayTreeBenchmark/SplayTreeInsert/1048576     806703688 ns  806717532 ns          1
SplayTreeBenchmark/SplayTreeInsertRec/1024        109911 ns     109949 ns       6373
SplayTreeBenchmark/SplayTreeInsertRec/4096        569791 ns     569847 ns       1213
SplayTreeBenchmark/SplayTreeInsertRec/16384      3595089 ns    3594448 ns        193
SplayTreeBenchmark/SplayTreeInsertRec/65536     20172641 ns   20173047 ns         35
SplayTreeBenchmark/SplayTreeInsertRec/262144   122857422 ns  122859899 ns          6
SplayTreeBenchmark/SplayTreeInsertRec/1048576  860131462 ns  860149827 ns          1
SplayTreeBenchmark/SplayTreeDelete/1024            77391 ns      77406 ns       8950
SplayTreeBenchmark/SplayTreeDelete/4096           401553 ns     401546 ns       1746
SplayTreeBenchmark/SplayTreeDelete/16384         2576609 ns    2576659 ns        272
SplayTreeBenchmark/SplayTreeDelete/65536        15056546 ns   15056647 ns         47
SplayTreeBenchmark/SplayTreeDelete/262144       92864529 ns   92865867 ns          8
SplayTreeBenchmark/SplayTreeDelete/1048576     812860246 ns  812871640 ns          1
SplayTreeBenchmark/SplayTreeDeleteRec/1024         90506 ns      90503 ns       7795
SplayTreeBenchmark/SplayTreeDeleteRec/4096        476729 ns     476734 ns       1476
SplayTreeBenchmark/SplayTreeDeleteRec/16384      2944560 ns    2944595 ns        238
SplayTreeBenchmark/SplayTreeDeleteRec/65536     16781355 ns   16781523 ns         42
SplayTreeBenchmark/SplayTreeDeleteRec/262144   101547873 ns  101549485 ns          7
SplayTreeBenchmark/SplayTreeDeleteRec/1048576  832879799 ns  832895096 ns          1
</pre>
