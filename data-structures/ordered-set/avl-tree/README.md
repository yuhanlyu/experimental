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
AVLTreeBenchmark/AVLTreeInsert/1024                  72628 ns      72235 ns       9682
AVLTreeBenchmark/AVLTreeInsert/4096                 347650 ns     347615 ns       2077
AVLTreeBenchmark/AVLTreeInsert/16384               1969666 ns    1969722 ns        357
AVLTreeBenchmark/AVLTreeInsert/65536              11038753 ns   11039022 ns         65
AVLTreeBenchmark/AVLTreeInsert/262144             73801868 ns   73802630 ns         11
AVLTreeBenchmark/AVLTreeInsert/1048576           611745160 ns  611748579 ns          2
AVLTreeBenchmark/AVLTreeRecursiveInsert/1024         89660 ns      89679 ns       7828
AVLTreeBenchmark/AVLTreeRecursiveInsert/4096        423173 ns     423176 ns       1654
AVLTreeBenchmark/AVLTreeRecursiveInsert/16384      2467116 ns    2467019 ns        290
AVLTreeBenchmark/AVLTreeRecursiveInsert/65536     13015728 ns   13015609 ns         54
AVLTreeBenchmark/AVLTreeRecursiveInsert/262144    75742422 ns   75742083 ns         10
AVLTreeBenchmark/AVLTreeRecursiveInsert/1048576  546857404 ns  546850044 ns          1
AVLTreeBenchmark/AVLTreeDelete/1024                  76162 ns      76156 ns       9202
AVLTreeBenchmark/AVLTreeDelete/4096                 368958 ns     368946 ns       1931
AVLTreeBenchmark/AVLTreeDelete/16384               2106325 ns    2106276 ns        333
AVLTreeBenchmark/AVLTreeDelete/65536              11615579 ns   11615369 ns         60
AVLTreeBenchmark/AVLTreeDelete/262144             84285326 ns   84283426 ns          9
AVLTreeBenchmark/AVLTreeDelete/1048576           592924746 ns  592911882 ns          1
</pre>
