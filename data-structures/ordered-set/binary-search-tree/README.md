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
BSTBenchmark/BinarySearchTreeInsert/1024                  56349 ns      56341 ns      12251
BSTBenchmark/BinarySearchTreeInsert/4096                 296901 ns     296935 ns       2336
BSTBenchmark/BinarySearchTreeInsert/16384               2056376 ns    2056396 ns        338
BSTBenchmark/BinarySearchTreeInsert/65536              12203142 ns   12203517 ns         57
BSTBenchmark/BinarySearchTreeInsert/262144             78259334 ns   78256196 ns          9
BSTBenchmark/BinarySearchTreeInsert/1048576           602241845 ns  602210200 ns          1
BSTBenchmark/BinarySearchTreeInsertRec/1024               74012 ns      74029 ns       9566
BSTBenchmark/BinarySearchTreeInsertRec/4096              366079 ns     366120 ns       1915
BSTBenchmark/BinarySearchTreeInsertRec/16384            2335335 ns    2335460 ns        298
BSTBenchmark/BinarySearchTreeInsertRec/65536           13343638 ns   13344237 ns         51
BSTBenchmark/BinarySearchTreeInsertRec/262144          84520710 ns   84522262 ns          9
BSTBenchmark/BinarySearchTreeInsertRec/1048576        619863815 ns  619856319 ns          1
BSTRemoveBenchmark/BinarySearchTreeRemove/1024            56152 ns      56151 ns      12616
BSTRemoveBenchmark/BinarySearchTreeRemove/4096           291736 ns     291756 ns       2422
BSTRemoveBenchmark/BinarySearchTreeRemove/16384         1910740 ns    1910735 ns        369
BSTRemoveBenchmark/BinarySearchTreeRemove/65536        11279579 ns   11279839 ns         63
BSTRemoveBenchmark/BinarySearchTreeRemove/262144       69395364 ns   69399357 ns         10
BSTRemoveBenchmark/BinarySearchTreeRemove/1048576     506222564 ns  506246647 ns          1
BSTRemoveBenchmark/BinarySearchTreeRemoveRec/1024         56650 ns      56642 ns      12396
BSTRemoveBenchmark/BinarySearchTreeRemoveRec/4096        292395 ns     292417 ns       2391
BSTRemoveBenchmark/BinarySearchTreeRemoveRec/16384      1917014 ns    1917097 ns        365
BSTRemoveBenchmark/BinarySearchTreeRemoveRec/65536     11381511 ns   11381837 ns         62
BSTRemoveBenchmark/BinarySearchTreeRemoveRec/262144    71720763 ns   71716833 ns         10
BSTRemoveBenchmark/BinarySearchTreeRemoveRec/1048576  520912216 ns  520922981 ns          1
</pre>
