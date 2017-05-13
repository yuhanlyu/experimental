## Binary search tree traversal
This module contains several [tree traversal](https://en.wikipedia.org/wiki/Tree_traversal)
methods, including inorder/preorder/postorder/levelorder traversal.

For each of inorder/preorder/postorder traversal, this module contains a
recursive version outputting to a vector, an iterative version using a stack 
outputting to a vector, an iterative version using a stack outputting to an
array, and a stackless version (Morris traversal) from the following paper:  
Joseph M. Morris   
[Traversing binary trees simply and cheaply](https://doi.org/10.1016/0020-0190(79)90068-1)

For levelorder traversal, this module contains a version of using one queue and
a version of using two vectors.

## Benchmark
For inorder/preorder/postorder traversal, the iterative version is slightly
faster than recursive version, and the recursive version is slightly faster
than the Morris traversal.

For levelorder traversal, using two vectors is slightly faster than using one
queue.
<pre>
---------------------------------------------------------------------------------------------
Benchmark                                                      Time           CPU Iterations
---------------------------------------------------------------------------------------------
BSTTraversalBenchmark/InorderTraverseRec/1024               3492 ns       3491 ns     244641
BSTTraversalBenchmark/InorderTraverseRec/4096              28781 ns      28781 ns      24922
BSTTraversalBenchmark/InorderTraverseRec/16384            183796 ns     183762 ns       3853
BSTTraversalBenchmark/InorderTraverseRec/65536            828823 ns     828829 ns        843
BSTTraversalBenchmark/InorderTraverseRec/262144          5202040 ns    5201136 ns        133
BSTTraversalBenchmark/InorderTraverseRec/1048576        45261038 ns   45260936 ns         16
BSTTraversalBenchmark/InorderTraverse/1024                  3130 ns       3130 ns     226829
BSTTraversalBenchmark/InorderTraverse/4096                 28008 ns      28008 ns      25247
BSTTraversalBenchmark/InorderTraverse/16384               178937 ns     178904 ns       3856
BSTTraversalBenchmark/InorderTraverse/65536               837242 ns     837246 ns        849
BSTTraversalBenchmark/InorderTraverse/262144             5223029 ns    5222139 ns        136
BSTTraversalBenchmark/InorderTraverse/1048576           44734599 ns   44735026 ns         16
BSTTraversalBenchmark/InorderTraverseArray/1024             2541 ns       2540 ns     280949
BSTTraversalBenchmark/InorderTraverseArray/4096            28349 ns      28349 ns      24921
BSTTraversalBenchmark/InorderTraverseArray/16384          176276 ns     176246 ns       3954
BSTTraversalBenchmark/InorderTraverseArray/65536          802140 ns     802138 ns        864
BSTTraversalBenchmark/InorderTraverseArray/262144        5024183 ns    5022954 ns        100
BSTTraversalBenchmark/InorderTraverseArray/1048576      42694556 ns   42694517 ns         17
BSTTraversalBenchmark/InorderTraverseMorris/1024            5692 ns       5691 ns     124817
BSTTraversalBenchmark/InorderTraverseMorris/4096           79411 ns      79411 ns       8746
BSTTraversalBenchmark/InorderTraverseMorris/16384         353573 ns     353516 ns       1990
BSTTraversalBenchmark/InorderTraverseMorris/65536        1635935 ns    1635950 ns        412
BSTTraversalBenchmark/InorderTraverseMorris/262144      15205710 ns   15203376 ns         50
BSTTraversalBenchmark/InorderTraverseMorris/1048576     56886181 ns   56876534 ns         12
BSTTraversalBenchmark/PreorderTraverseRec/1024              4791 ns       4791 ns     149068
BSTTraversalBenchmark/PreorderTraverseRec/4096             37224 ns      37223 ns      18703
BSTTraversalBenchmark/PreorderTraverseRec/16384           202429 ns     202395 ns       3391
BSTTraversalBenchmark/PreorderTraverseRec/65536           892047 ns     892046 ns        802
BSTTraversalBenchmark/PreorderTraverseRec/262144         5507057 ns    5507107 ns        130
BSTTraversalBenchmark/PreorderTraverseRec/1048576       42431958 ns   42432233 ns         16
BSTTraversalBenchmark/PreorderTraverse/1024                 3511 ns       3510 ns     223674
BSTTraversalBenchmark/PreorderTraverse/4096                30877 ns      30877 ns      22951
BSTTraversalBenchmark/PreorderTraverse/16384              198861 ns     198829 ns       3571
BSTTraversalBenchmark/PreorderTraverse/65536              884202 ns     884206 ns        788
BSTTraversalBenchmark/PreorderTraverse/262144            5170358 ns    5169336 ns        136
BSTTraversalBenchmark/PreorderTraverse/1048576          42383647 ns   42383724 ns         17
BSTTraversalBenchmark/PreorderTraverseArray/1024            2406 ns       2405 ns     291690
BSTTraversalBenchmark/PreorderTraverseArray/4096           26807 ns      26807 ns      26320
BSTTraversalBenchmark/PreorderTraverseArray/16384         171845 ns     171816 ns       4079
BSTTraversalBenchmark/PreorderTraverseArray/65536         779200 ns     779203 ns        896
BSTTraversalBenchmark/PreorderTraverseArray/262144       4818490 ns    4817593 ns        136
BSTTraversalBenchmark/PreorderTraverseArray/1048576     39046686 ns   39046633 ns         18
BSTTraversalBenchmark/PreorderTraverseMorris/1024           5188 ns       5188 ns     128898
BSTTraversalBenchmark/PreorderTraverseMorris/4096          80941 ns      80941 ns       8600
BSTTraversalBenchmark/PreorderTraverseMorris/16384        358693 ns     358696 ns       1998
BSTTraversalBenchmark/PreorderTraverseMorris/65536       1653159 ns    1653172 ns        418
BSTTraversalBenchmark/PreorderTraverseMorris/262144     13871519 ns   13869180 ns         50
BSTTraversalBenchmark/PreorderTraverseMorris/1048576    55559274 ns   55549681 ns         12
BSTTraversalBenchmark/PostorderTraverseRec/1024             6240 ns       6240 ns     109491
BSTTraversalBenchmark/PostorderTraverseRec/4096            48035 ns      48027 ns      14392
BSTTraversalBenchmark/PostorderTraverseRec/16384          245671 ns     245673 ns       2847
BSTTraversalBenchmark/PostorderTraverseRec/65536         1036949 ns    1036762 ns        677
BSTTraversalBenchmark/PostorderTraverseRec/262144        6684708 ns    6684752 ns        103
BSTTraversalBenchmark/PostorderTraverseRec/1048576      52119910 ns   52119755 ns         13
BSTTraversalBenchmark/PostorderTraverse/1024                3477 ns       3476 ns     187000
BSTTraversalBenchmark/PostorderTraverse/4096               37758 ns      37758 ns      18695
BSTTraversalBenchmark/PostorderTraverse/16384             234786 ns     234745 ns       2966
BSTTraversalBenchmark/PostorderTraverse/65536            1045395 ns    1045398 ns        675
BSTTraversalBenchmark/PostorderTraverse/262144           6378509 ns    6377405 ns        108
BSTTraversalBenchmark/PostorderTraverse/1048576         52069387 ns   52059511 ns         13
BSTTraversalBenchmark/PostorderTraverseArray/1024          28194 ns      28177 ns      24990
BSTTraversalBenchmark/PostorderTraverseArray/4096         118343 ns     118297 ns       5840
BSTTraversalBenchmark/PostorderTraverseArray/16384        585504 ns     585449 ns       1167
BSTTraversalBenchmark/PostorderTraverseArray/65536       2597653 ns    2597592 ns        269
BSTTraversalBenchmark/PostorderTraverseArray/262144     16324130 ns   16323881 ns         43
BSTTraversalBenchmark/PostorderTraverseArray/1048576   139693343 ns  139669505 ns          5
BSTTraversalBenchmark/PostorderTraverseMorris/1024          3457 ns       3457 ns     198870
BSTTraversalBenchmark/PostorderTraverseMorris/4096         41366 ns      41359 ns      17034
BSTTraversalBenchmark/PostorderTraverseMorris/16384       255057 ns     255058 ns       2759
BSTTraversalBenchmark/PostorderTraverseMorris/65536      1160562 ns    1160354 ns        605
BSTTraversalBenchmark/PostorderTraverseMorris/262144     7475008 ns    7474369 ns         97
BSTTraversalBenchmark/PostorderTraverseMorris/1048576   66301827 ns   66301101 ns         11
BSTTraversalBenchmark/LevelOrderTraverseQueue/1024          3008 ns       3007 ns     226894
BSTTraversalBenchmark/LevelOrderTraverseQueue/4096         30444 ns      30444 ns      22662
BSTTraversalBenchmark/LevelOrderTraverseQueue/16384       165391 ns     165364 ns       4230
BSTTraversalBenchmark/LevelOrderTraverseQueue/65536       684105 ns     684106 ns       1035
BSTTraversalBenchmark/LevelOrderTraverseQueue/262144     4241047 ns    4240517 ns        168
BSTTraversalBenchmark/LevelOrderTraverseQueue/1048576   24315947 ns   24315706 ns         29
BSTTraversalBenchmark/LevelOrderTraverse/1024               2910 ns       2910 ns     246021
BSTTraversalBenchmark/LevelOrderTraverse/4096              23407 ns      23407 ns      29484
BSTTraversalBenchmark/LevelOrderTraverse/16384            134874 ns     134851 ns       5257
BSTTraversalBenchmark/LevelOrderTraverse/65536            547625 ns     547624 ns       1287
BSTTraversalBenchmark/LevelOrderTraverse/262144          3414172 ns    3414162 ns        208
BSTTraversalBenchmark/LevelOrderTraverse/1048576        19387118 ns   19387026 ns         36
</pre>
