## WAVL tree
[WAVL tree](https://en.wikipedia.org/wiki/WAVL_tree) is self-balancing binary search
tree. The operations of insertion and deletion can be done in O(lg n) time in
worst case.

In the worst case, insertion and deletion only perform two rotations (one signle
rotation or one double rotation).

The standard algorithm is from the following paper:
Bernhard Haeupler, Siddhartha Sen, Robert E. Tarjan
[Rank-Balanced Trees](https://doi.org/10.1145/2689412)
ACM Transactions on Algorithms (TALG), Volume 11, Issue 4
Article No.: 30, Pages 1 - 26

The wavl.h implements two algorithms without parent pointers. Insert/Delete uses safe node technique,
while RecursiveInsert/RecursiveDelete uses recursion.

## Benchmark
<pre>
------------------------------------------------------------------------------------
Benchmark                                          Time             CPU   Iterations
------------------------------------------------------------------------------------
WAVLBenchmark/WAVLStandardInsert/1024          70851 ns        70844 ns         9609
WAVLBenchmark/WAVLStandardInsert/4096         329610 ns       329598 ns         2034
WAVLBenchmark/WAVLStandardInsert/16384       1685903 ns      1685957 ns          414
WAVLBenchmark/WAVLStandardInsert/65536       9410940 ns      9411022 ns           67
WAVLBenchmark/WAVLStandardInsert/262144     69770474 ns     69771957 ns           12
WAVLBenchmark/WAVLStandardInsert/1048576   603474964 ns    603468300 ns            1
WAVLBenchmark/WAVLStandardDelete/1024          69725 ns        69678 ns        10190
WAVLBenchmark/WAVLStandardDelete/4096         382113 ns       382110 ns         1743
WAVLBenchmark/WAVLStandardDelete/16384       2235886 ns      2235931 ns          313
WAVLBenchmark/WAVLStandardDelete/65536      13487607 ns     13488455 ns           53
WAVLBenchmark/WAVLStandardDelete/262144     91902409 ns     91902241 ns            8
WAVLBenchmark/WAVLStandardDelete/1048576   569572534 ns    569570977 ns            1
WAVLBenchmark/WAVLStandardMix/1024             17413 ns        17357 ns        44680
WAVLBenchmark/WAVLStandardMix/4096             86928 ns        86842 ns         7149
WAVLBenchmark/WAVLStandardMix/16384           501740 ns       501555 ns         1548
WAVLBenchmark/WAVLStandardMix/65536          2805401 ns      2805087 ns          276
WAVLBenchmark/WAVLStandardMix/262144        20272254 ns     20272241 ns           39
WAVLBenchmark/WAVLStandardMix/1048576       81524660 ns     81523618 ns            9
WAVLBenchmark/WAVLInsert/1024                 107003 ns       106987 ns         6463
WAVLBenchmark/WAVLInsert/4096                 508304 ns       508359 ns         1389
WAVLBenchmark/WAVLInsert/16384               2501761 ns      2501817 ns          279
WAVLBenchmark/WAVLInsert/65536              13320017 ns     13320483 ns           52
WAVLBenchmark/WAVLInsert/262144             80790348 ns     80792394 ns           10
WAVLBenchmark/WAVLInsert/1048576           557565013 ns    557565196 ns            1
WAVLBenchmark/WAVLRecursiveInsert/1024        106887 ns       106896 ns         6651
WAVLBenchmark/WAVLRecursiveInsert/4096        580032 ns       580292 ns         1207
WAVLBenchmark/WAVLRecursiveInsert/16384      3818284 ns      3819031 ns          190
WAVLBenchmark/WAVLRecursiveInsert/65536     23308779 ns     23310276 ns           28
WAVLBenchmark/WAVLRecursiveInsert/262144   156183970 ns    156186030 ns            4
WAVLBenchmark/WAVLRecursiveInsert/1048576  968012109 ns    968014594 ns            1
WAVLBenchmark/WAVLRecursiveDelete/1024        115518 ns       115473 ns         6162
WAVLBenchmark/WAVLRecursiveDelete/4096        563547 ns       563501 ns         1241
WAVLBenchmark/WAVLRecursiveDelete/16384      3262579 ns      3262376 ns          217
WAVLBenchmark/WAVLRecursiveDelete/65536     21690562 ns     21690373 ns           33
WAVLBenchmark/WAVLRecursiveDelete/262144   137632319 ns    137632022 ns            5
WAVLBenchmark/WAVLRecursiveDelete/1048576  758496259 ns    758494198 ns            1
</pre>
