## Binary search tree
[Binary search tree](https://en.wikipedia.org/wiki/Binary_search_tree) is a
simple way to maintain ordered set. This module contains a naive
implementation of binary search tree.

## Benchmark
The performance of iterative/recursive insertion/removal are compared. The
iterative version uses only O(1) space while the recursive version uses O(h)
space, where h is the height of the tree.  The iterative version seems slightly
faster.
<pre>
--------------------------------------------------------------------------------------------
Benchmark                                                     Time           CPU Iterations
--------------------------------------------------------------------------------------------
BSTBenchmark/BinarySearchTreeInsert/1024                  57072 ns      57079 ns      12154
BSTBenchmark/BinarySearchTreeInsert/4096                 307728 ns     307753 ns       2265
BSTBenchmark/BinarySearchTreeInsert/16384               2007437 ns    2007496 ns        350
BSTBenchmark/BinarySearchTreeInsert/65536              11824707 ns   11803195 ns         59
BSTBenchmark/BinarySearchTreeInsert/262144             91100634 ns   91099195 ns          9
BSTBenchmark/BinarySearchTreeInsert/1048576           671699807 ns  671637096 ns          1
BSTBenchmark/BinarySearchTreeInsertRec/1024               74088 ns      74105 ns       9438
BSTBenchmark/BinarySearchTreeInsertRec/4096              378921 ns     378928 ns       1846
BSTBenchmark/BinarySearchTreeInsertRec/16384            2357873 ns    2357921 ns        297
BSTBenchmark/BinarySearchTreeInsertRec/65536           13516561 ns   13516543 ns         51
BSTBenchmark/BinarySearchTreeInsertRec/262144          96193576 ns   96192601 ns          8
BSTBenchmark/BinarySearchTreeInsertRec/1048576        689502338 ns  689490184 ns          1
BSTRemoveBenchmark/BinarySearchTreeRemove/1024            42646 ns      42643 ns      16404
BSTRemoveBenchmark/BinarySearchTreeRemove/4096           232607 ns     232599 ns       3002
BSTRemoveBenchmark/BinarySearchTreeRemove/16384         1679703 ns    1679668 ns        421
BSTRemoveBenchmark/BinarySearchTreeRemove/65536        10302350 ns   10302230 ns         70
BSTRemoveBenchmark/BinarySearchTreeRemove/262144       76596037 ns   76594994 ns         10
BSTRemoveBenchmark/BinarySearchTreeRemove/1048576     557523421 ns  557515146 ns          1
BSTRemoveBenchmark/BinarySearchTreeRemoveRec/1024         57963 ns      57960 ns      12039
BSTRemoveBenchmark/BinarySearchTreeRemoveRec/4096        302862 ns     302856 ns       2304
BSTRemoveBenchmark/BinarySearchTreeRemoveRec/16384      1959876 ns    1959810 ns        355
BSTRemoveBenchmark/BinarySearchTreeRemoveRec/65536     11649414 ns   11649263 ns         60
BSTRemoveBenchmark/BinarySearchTreeRemoveRec/262144    83962331 ns   83960968 ns          9
BSTRemoveBenchmark/BinarySearchTreeRemoveRec/1048576  579015506 ns  579009873 ns          1
</pre>
