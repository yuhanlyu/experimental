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
BSTBenchmark/BinarySearchTreeInsert/1024                  57136 ns      56729 ns      12152
BSTBenchmark/BinarySearchTreeInsert/4096                 301564 ns     299168 ns       2334
BSTBenchmark/BinarySearchTreeInsert/16384               2094872 ns    2081139 ns        334
BSTBenchmark/BinarySearchTreeInsert/65536              12442364 ns   12440137 ns         55
BSTBenchmark/BinarySearchTreeInsert/262144             92320142 ns   91906284 ns          9
BSTBenchmark/BinarySearchTreeInsert/1048576           684404710 ns  676590828 ns          1
BSTBenchmark/BinarySearchTreeInsertRec/1024               74793 ns      74247 ns       9384
BSTBenchmark/BinarySearchTreeInsertRec/4096              373331 ns     371326 ns       1884
BSTBenchmark/BinarySearchTreeInsertRec/16384            2376999 ns    2359025 ns        294
BSTBenchmark/BinarySearchTreeInsertRec/65536           13705912 ns   13584831 ns         51
BSTBenchmark/BinarySearchTreeInsertRec/262144          95658629 ns   95207039 ns          8
BSTBenchmark/BinarySearchTreeInsertRec/1048576        691794371 ns  686559304 ns          1
BSTRemoveBenchmark/BinarySearchTreeRemove/1024            42717 ns      42373 ns      16488
BSTRemoveBenchmark/BinarySearchTreeRemove/4096           230172 ns     228521 ns       3078
BSTRemoveBenchmark/BinarySearchTreeRemove/16384         1693828 ns    1688887 ns        415
BSTRemoveBenchmark/BinarySearchTreeRemove/65536        10353592 ns   10258887 ns         69
BSTRemoveBenchmark/BinarySearchTreeRemove/262144       80447525 ns   79505002 ns         11
BSTRemoveBenchmark/BinarySearchTreeRemove/1048576     570871472 ns  564397771 ns          1
BSTRemoveBenchmark/BinarySearchTreeRemoveRec/1024         57588 ns      57104 ns      12302
BSTRemoveBenchmark/BinarySearchTreeRemoveRec/4096        296922 ns     294658 ns       2366
BSTRemoveBenchmark/BinarySearchTreeRemoveRec/16384      1962740 ns    1947541 ns        359
BSTRemoveBenchmark/BinarySearchTreeRemoveRec/65536     11733916 ns   11623410 ns         60
BSTRemoveBenchmark/BinarySearchTreeRemoveRec/262144    84001732 ns   83021441 ns         10
BSTRemoveBenchmark/BinarySearchTreeRemoveRec/1048576  595244754 ns  592433928 ns          1
</pre>
