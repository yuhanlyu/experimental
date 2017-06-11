## Binary search tree
[Treap](https://en.wikipedia.org/wiki/Treap) is a randomized self-balancing
binary search tree. The operations of insertion and deletion can be done in
O(lg n) time in expectation.

There are two implementations in this module. One implementation uses rotations
when doing insert/delete. Another implementation does not use rotations.
1. Insert: insert a value using rotations and recursion.
1. Delete: delete a value using rotations.
1. InsertWithoutRotation: insert a value without rotations. But this method
   cannot detect duplicated insertion.
1. DeleteWithoutRotation: delete a value without rotations.

## Benchmark
Insert/Delete without rotations seems faster than the original method described
in the paper.
<pre>
-----------------------------------------------------------------------------------------
Benchmark                                                  Time           CPU Iterations
-----------------------------------------------------------------------------------------
TreapBenchmark/TreapInsert/1024                       120952 ns     120988 ns       5707
TreapBenchmark/TreapInsert/4096                       590842 ns     590948 ns       1176
TreapBenchmark/TreapInsert/16384                     3310175 ns    3310458 ns        210
TreapBenchmark/TreapInsert/65536                    18473205 ns   18474659 ns         37
TreapBenchmark/TreapInsert/262144                  144342513 ns  144350553 ns          6
TreapBenchmark/TreapInsert/1048576                 915602047 ns  913382690 ns          1
TreapBenchmark/TreapDelete/1024                        74373 ns      74314 ns       9317
TreapBenchmark/TreapDelete/4096                       475054 ns     475042 ns       1472
TreapBenchmark/TreapDelete/16384                     3106742 ns    3106719 ns        229
TreapBenchmark/TreapDelete/65536                    21989357 ns   21991139 ns         31
TreapBenchmark/TreapDelete/262144                  142160690 ns  142168520 ns          5
TreapBenchmark/TreapDelete/1048576                 832655520 ns  832701624 ns          1

-----------------------------------------------------------------------------------------
Benchmark                                                  Time           CPU Iterations
-----------------------------------------------------------------------------------------
TreapBenchmark/TreapInsertWithoutRotation/1024         81463 ns      81334 ns       8464
TreapBenchmark/TreapInsertWithoutRotation/4096        425331 ns     425371 ns       1668
TreapBenchmark/TreapInsertWithoutRotation/16384      2799359 ns    2799478 ns        250
TreapBenchmark/TreapInsertWithoutRotation/65536     16443520 ns   16402285 ns         43
TreapBenchmark/TreapInsertWithoutRotation/262144   134721600 ns  134472696 ns          6
TreapBenchmark/TreapInsertWithoutRotation/1048576  912164152 ns  912180108 ns          1
TreapBenchmark/TreapDeleteWithoutRotation/1024         72617 ns      72648 ns       9568
TreapBenchmark/TreapDeleteWithoutRotation/4096        463579 ns     463544 ns       1511
TreapBenchmark/TreapDeleteWithoutRotation/16384      3047519 ns    3047552 ns        227
TreapBenchmark/TreapDeleteWithoutRotation/65536     21832525 ns   21833010 ns         33
TreapBenchmark/TreapDeleteWithoutRotation/262144   140607770 ns  140610778 ns          5
TreapBenchmark/TreapDeleteWithoutRotation/1048576  839457914 ns  839475488 ns          1
</pre>
