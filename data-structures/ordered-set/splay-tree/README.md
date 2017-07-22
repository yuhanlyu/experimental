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
SplayTreeBenchmark/SplayTreeInsert/1024            92026 ns      92048 ns       7616
SplayTreeBenchmark/SplayTreeInsert/4096           493226 ns     493246 ns       1414
SplayTreeBenchmark/SplayTreeInsert/16384         3254825 ns    3253998 ns        217
SplayTreeBenchmark/SplayTreeInsert/65536        18851735 ns   18852069 ns         37
SplayTreeBenchmark/SplayTreeInsert/262144      132488276 ns  132458441 ns          7
SplayTreeBenchmark/SplayTreeInsert/1048576     894192301 ns  894170592 ns          1
SplayTreeBenchmark/SplayTreeInsertRec/1024        107773 ns     107810 ns       6556
SplayTreeBenchmark/SplayTreeInsertRec/4096        572395 ns     572406 ns       1164
SplayTreeBenchmark/SplayTreeInsertRec/16384      3615899 ns    3615927 ns        197
SplayTreeBenchmark/SplayTreeInsertRec/65536     20602092 ns   20602463 ns         34
SplayTreeBenchmark/SplayTreeInsertRec/262144   139648563 ns  139468781 ns          6
SplayTreeBenchmark/SplayTreeInsertRec/1048576  933255683 ns  933260942 ns          1
SplayTreeBenchmark/SplayTreeDelete/1024            74191 ns      74190 ns       9451
SplayTreeBenchmark/SplayTreeDelete/4096           396784 ns     396778 ns       1753
SplayTreeBenchmark/SplayTreeDelete/16384         2535412 ns    2535416 ns        279
SplayTreeBenchmark/SplayTreeDelete/65536        14889242 ns   14888003 ns         47
SplayTreeBenchmark/SplayTreeDelete/262144      103644655 ns  103642366 ns          7
SplayTreeBenchmark/SplayTreeDelete/1048576     868114948 ns  868117896 ns          1
SplayTreeBenchmark/SplayTreeDeleteRec/1024         86671 ns      86663 ns       8100
SplayTreeBenchmark/SplayTreeDeleteRec/4096        464882 ns     464875 ns       1516
SplayTreeBenchmark/SplayTreeDeleteRec/16384      2858536 ns    2858433 ns        247
SplayTreeBenchmark/SplayTreeDeleteRec/65536     16630637 ns   16630148 ns         43
SplayTreeBenchmark/SplayTreeDeleteRec/262144   113114315 ns  113115422 ns          6
SplayTreeBenchmark/SplayTreeDeleteRec/1048576  894834371 ns  894791996 ns          1
</pre>
