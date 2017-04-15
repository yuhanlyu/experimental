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
BSTBenchmark/BinarySearchTreeInsert/1024                  57708 ns      57727 ns      11523
BSTBenchmark/BinarySearchTreeInsert/4096                 311015 ns     311040 ns       2237
BSTBenchmark/BinarySearchTreeInsert/16384               2014775 ns    2014830 ns        345
BSTBenchmark/BinarySearchTreeInsert/65536              11784751 ns   11784871 ns         59
BSTBenchmark/BinarySearchTreeInsert/262144             91473494 ns   91474392 ns          7
BSTBenchmark/BinarySearchTreeInsert/1048576           684605243 ns  684606022 ns          1
BSTBenchmark/BinarySearchTreeInsertRec/1024               73731 ns      73756 ns       9618
BSTBenchmark/BinarySearchTreeInsertRec/4096              376054 ns     376025 ns       1861
BSTBenchmark/BinarySearchTreeInsertRec/16384            2317334 ns    2317356 ns        299
BSTBenchmark/BinarySearchTreeInsertRec/65536           13416534 ns   13416783 ns         50
BSTBenchmark/BinarySearchTreeInsertRec/262144          99417262 ns   99418374 ns          8
BSTBenchmark/BinarySearchTreeInsertRec/1048576        697869161 ns  697867000 ns          1
BSTRemoveBenchmark/BinarySearchTreeRemove/1024            57314 ns      57316 ns      12169
BSTRemoveBenchmark/BinarySearchTreeRemove/4096           302382 ns     302389 ns       2322
BSTRemoveBenchmark/BinarySearchTreeRemove/16384         1936916 ns    1936925 ns        363
BSTRemoveBenchmark/BinarySearchTreeRemove/65536        11587557 ns   11587635 ns         61
BSTRemoveBenchmark/BinarySearchTreeRemove/262144       83871549 ns   83871473 ns         10
BSTRemoveBenchmark/BinarySearchTreeRemove/1048576     596343221 ns  596330571 ns          1
BSTRemoveBenchmark/BinarySearchTreeRemoveRec/1024         57809 ns      57812 ns      12147
BSTRemoveBenchmark/BinarySearchTreeRemoveRec/4096        302470 ns     302481 ns       2317
BSTRemoveBenchmark/BinarySearchTreeRemoveRec/16384      1944772 ns    1944819 ns        360
BSTRemoveBenchmark/BinarySearchTreeRemoveRec/65536     11565469 ns   11565407 ns         62
BSTRemoveBenchmark/BinarySearchTreeRemoveRec/262144    85480856 ns   85478983 ns         10
BSTRemoveBenchmark/BinarySearchTreeRemoveRec/1048576  596580534 ns  596576651 ns          1
</pre>
