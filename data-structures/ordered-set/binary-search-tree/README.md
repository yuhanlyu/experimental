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
--------------------------------------------------------------------------------------
Benchmark                                               Time           CPU Iterations
--------------------------------------------------------------------------------------
BSTBenchmark/BinarySearchTreeInsert/1024            57215 ns      56907 ns      12078
BSTBenchmark/BinarySearchTreeInsert/4096           297912 ns     297929 ns       2358
BSTBenchmark/BinarySearchTreeInsert/16384         1993355 ns    1992505 ns        348
BSTBenchmark/BinarySearchTreeInsert/65536        11600612 ns   11600536 ns         60
BSTBenchmark/BinarySearchTreeInsert/262144       80428632 ns   80429366 ns         10
BSTBenchmark/BinarySearchTreeInsert/1048576     594591291 ns  594594828 ns          1
BSTBenchmark/BinarySearchTreeInsertRec/1024         71508 ns      71527 ns       9718
BSTBenchmark/BinarySearchTreeInsertRec/4096        359052 ns     359066 ns       1960
BSTBenchmark/BinarySearchTreeInsertRec/16384      2289280 ns    2289084 ns        303
BSTBenchmark/BinarySearchTreeInsertRec/65536     13186900 ns   13186920 ns         53
BSTBenchmark/BinarySearchTreeInsertRec/262144    83687318 ns   83688364 ns          9
BSTBenchmark/BinarySearchTreeInsertRec/1048576  619366917 ns  619370299 ns          1
BSTBenchmark/BinarySearchTreeDelete/1024            42840 ns      42828 ns      16436
BSTBenchmark/BinarySearchTreeDelete/4096           228138 ns     228129 ns       3099
BSTBenchmark/BinarySearchTreeDelete/16384         1647570 ns    1647480 ns        425
BSTBenchmark/BinarySearchTreeDelete/65536        10062064 ns   10062051 ns         71
BSTBenchmark/BinarySearchTreeDelete/262144       67385947 ns   67386124 ns         12
BSTBenchmark/BinarySearchTreeDelete/1048576     509659084 ns  509661268 ns          1
BSTBenchmark/BinarySearchTreeDeleteRec/1024         56177 ns      56162 ns      12474
BSTBenchmark/BinarySearchTreeDeleteRec/4096        288772 ns     288767 ns       2435
BSTBenchmark/BinarySearchTreeDeleteRec/16384      1912315 ns    1912329 ns        370
BSTBenchmark/BinarySearchTreeDeleteRec/65536     11240884 ns   11240901 ns         63
BSTBenchmark/BinarySearchTreeDeleteRec/262144    70715630 ns   70716262 ns         11
BSTBenchmark/BinarySearchTreeDeleteRec/1048576  551035215 ns  551033849 ns          1
</pre>
