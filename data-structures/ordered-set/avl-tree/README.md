## AVL tree
[AVL tree](https://en.wikipedia.org/wiki/AVL_tree) is self-balancing binary search
tree. The operations of insertion and deletion can be done in O(lg n) time in
worst case.

This module implements two versions of insertion: iterative and recursive.

## Benchmark
<pre>
------------------------------------------------------------------------------
Benchmark                                       Time           CPU Iterations
------------------------------------------------------------------------------
AVLTreeBenchmark/AVLTreeInsert/1024         72937 ns      72948 ns       9595
AVLTreeBenchmark/AVLTreeInsert/4096        348960 ns     348985 ns       2008
AVLTreeBenchmark/AVLTreeInsert/16384      2148532 ns    2148662 ns        327
AVLTreeBenchmark/AVLTreeInsert/65536     12520012 ns   12520554 ns         56
AVLTreeBenchmark/AVLTreeInsert/262144    92225872 ns   92219973 ns          9
AVLTreeBenchmark/AVLTreeInsert/1048576  666060821 ns  666043249 ns          1

---------------------------------------------------------------------------------------
Benchmark                                                Time           CPU Iterations
---------------------------------------------------------------------------------------
AVLTreeBenchmark/AVLTreeRecursiveInsert/1024         81015 ns      81038 ns       8682
AVLTreeBenchmark/AVLTreeRecursiveInsert/4096        392373 ns     392416 ns       1800
AVLTreeBenchmark/AVLTreeRecursiveInsert/16384      2319821 ns    2319940 ns        303
AVLTreeBenchmark/AVLTreeRecursiveInsert/65536     13099606 ns   13100278 ns         54
AVLTreeBenchmark/AVLTreeRecursiveInsert/262144    99317652 ns   99318749 ns          8
AVLTreeBenchmark/AVLTreeRecursiveInsert/1048576  711118690 ns  711123539 ns          1

------------------------------------------------------------------------------
Benchmark                                       Time           CPU Iterations
------------------------------------------------------------------------------
AVLTreeBenchmark/AVLTreeDelete/1024         75716 ns      75713 ns       9241
AVLTreeBenchmark/AVLTreeDelete/4096        370785 ns     370760 ns       1885
AVLTreeBenchmark/AVLTreeDelete/16384      2218886 ns    2218832 ns        317
AVLTreeBenchmark/AVLTreeDelete/65536     12511040 ns   12510510 ns         56
AVLTreeBenchmark/AVLTreeDelete/262144    94937598 ns   94929954 ns          8
AVLTreeBenchmark/AVLTreeDelete/1048576  673104485 ns  673095207 ns          1

</pre>
