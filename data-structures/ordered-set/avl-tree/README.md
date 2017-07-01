## Binary search tree
[AVL tree](https://en.wikipedia.org/wiki/AVL_tree) is self-balancing binary search
tree. The operations of insertion and deletion can be done in O(lg n) time in
worst case.

This module implements two versions of insertion: iterative and recursive.

## Benchmark
<pre>
---------------------------------------------------------------------------------------
Benchmark                                                Time           CPU Iterations
---------------------------------------------------------------------------------------
AVLTreeBenchmark/AVLTreeInsert/1024                  73935 ns      73955 ns       9368
AVLTreeBenchmark/AVLTreeInsert/4096                 354298 ns     354322 ns       1966
AVLTreeBenchmark/AVLTreeInsert/16384               2138426 ns    2138484 ns        325
AVLTreeBenchmark/AVLTreeInsert/65536              11893950 ns   11893976 ns         56
AVLTreeBenchmark/AVLTreeInsert/262144             87799816 ns   87798465 ns          9
AVLTreeBenchmark/AVLTreeInsert/1048576           603889226 ns  603877076 ns          1
AVLTreeBenchmark/AVLTreeRecursiveInsert/1024         91859 ns      91887 ns       7606
AVLTreeBenchmark/AVLTreeRecursiveInsert/4096        428597 ns     428631 ns       1636
AVLTreeBenchmark/AVLTreeRecursiveInsert/16384      2393749 ns    2393756 ns        289
AVLTreeBenchmark/AVLTreeRecursiveInsert/65536     13019065 ns   13019302 ns         54
AVLTreeBenchmark/AVLTreeRecursiveInsert/262144    98832131 ns   98829997 ns          7
AVLTreeBenchmark/AVLTreeRecursiveInsert/1048576  626889596 ns  626654298 ns          1
AVLTreeBenchmark/AVLTreeDelete/1024                  76162 ns      76156 ns       9202
AVLTreeBenchmark/AVLTreeDelete/4096                 368958 ns     368946 ns       1931
AVLTreeBenchmark/AVLTreeDelete/16384               2106325 ns    2106276 ns        333
AVLTreeBenchmark/AVLTreeDelete/65536              11615579 ns   11615369 ns         60
AVLTreeBenchmark/AVLTreeDelete/262144             84285326 ns   84283426 ns          9
AVLTreeBenchmark/AVLTreeDelete/1048576           592924746 ns  592911882 ns          1
</pre>
