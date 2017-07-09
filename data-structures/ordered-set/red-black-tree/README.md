## Binary search tree
[Red-black tree](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree) is self-balancing binary search
tree. The operations of insertion and deletion can be done in O(lg n) time in
worst case.

This module implements three versions of insertion/deletion:
1. Iterative bottom-up: this is the method inspired by the technical report:  
   Robert Endre Tarjan  
   [Efficient Top-Down Updating of Red-Black Trees](https://www.cs.princeton.edu/research/techreps/TR-006-85)
1. Recursive bottom-up: this is the method proposed in the following paper:  
   Robert Endre Tarjan  
   [Updating a balanced search tree in O(1) rotations](https://doi.org/10.1016/0020-0190(83)90099-6)
1. Iterative top-down: this is the method proposed int the red-black paper:  
   Robert Sedgewick and Leo J. Guibas  
   [A dichromatic framework for balanced trees](https://doi.org/10.1109/SFCS.1978.3)

The top-down method is explained in Mark Allen Weiss's Data Structures and
Algorithm Analysis. The idea is that when traverse down the tree, rotate the
tree so that no rebalance is needed after insert/delete. Although this
iterative method uses only one pass and constant space, rebalancing takes
O(lg n) time.

The bottom-up method is explained in detail in CLRS. The idea is to rebalance
only necessary part to fix constraint violation due to insert/delete. The
rebalance (recolor/rotation) only takes amortized O(1) time. The method
explained in CLRS uses parent pointer so that when rebalance is done, the
procedure can quickly terminate. My implementation does not use parent pointer,
but uses recursion. Hence, even when the rebalance is done, the program still
need to backtrack to the root.

In the paper "Efficient Top-Down Updating of Red-Black Trees," Tarjan proposes
a top-down algorithm so that rebalancing takes only amortized O(1) time. Tarjan
notices that in the bottom-up method, during the insertion the rebalancing
terminates at the latest node along the search path that has at least one black
child, while during the deletion the rebalancing terminates at the latest node
along the search path that is red or has red child/grandchild. These properties
inspire my iterative bottom-up implementation.

My iterative bottom-up implementation uses constant space without parent
pointers. The idea is that when traverse down the tree, locate the node where
the rebalance terminates (safe node). Then, rebalance the tree in the second
pass from the safe node to the bottom, which takes amortized O(1) time. The
price is the time spent in finding the safe node.

My iterative bottom-up implementation is not an one pass algorithm, which
differs from Tarjan's proposal. In order to make my bottom-up implementation
one pass, 8 levels lookahead in insertion and 4 levels lookahead are required.

## Benchmark

For insert, my iterative bottom-up is faster than recursive bottom-up method,
top-down, and STL insert (non-recursive bottom-up method with parent pointers).
For delete, my iterative bottom-up method is slower than recursive bottom-up
method due to the time spent in finding the safe node.

<pre>
----------------------------------------------------------------------------
Benchmark                                     Time           CPU Iterations
----------------------------------------------------------------------------
RBTreeBenchmark/RBTreeInsert/1024         72671 ns      72696 ns       9634
RBTreeBenchmark/RBTreeInsert/4096        350203 ns     350230 ns       2012
RBTreeBenchmark/RBTreeInsert/16384      2065692 ns    2065850 ns        342
RBTreeBenchmark/RBTreeInsert/65536     11785963 ns   11786035 ns         60
RBTreeBenchmark/RBTreeInsert/262144    84199942 ns   84198404 ns         10
RBTreeBenchmark/RBTreeInsert/1048576  585882461 ns  585871519 ns          1

------------------------------------------------------------------------------------
Benchmark                                             Time           CPU Iterations
------------------------------------------------------------------------------------
RBTreeBenchmark/RBTreeBottomUpInsert/1024         96379 ns      96409 ns       7279
RBTreeBenchmark/RBTreeBottomUpInsert/4096        460877 ns     460925 ns       1518
RBTreeBenchmark/RBTreeBottomUpInsert/16384      2557981 ns    2558015 ns        269
RBTreeBenchmark/RBTreeBottomUpInsert/65536     14127775 ns   14127848 ns         48
RBTreeBenchmark/RBTreeBottomUpInsert/262144    99287042 ns   99286047 ns          8
RBTreeBenchmark/RBTreeBottomUpInsert/1048576  675040191 ns  675033237 ns          1

-----------------------------------------------------------------------------------
Benchmark                                            Time           CPU Iterations
-----------------------------------------------------------------------------------
RBTreeBenchmark/RBTreeTopDownInsert/1024         86919 ns      86952 ns       8042
RBTreeBenchmark/RBTreeTopDownInsert/4096        415141 ns     415156 ns       1682
RBTreeBenchmark/RBTreeTopDownInsert/16384      2362899 ns    2363112 ns        298
RBTreeBenchmark/RBTreeTopDownInsert/65536     13281022 ns   13280742 ns         53
RBTreeBenchmark/RBTreeTopDownInsert/262144    91618990 ns   91605778 ns          9
RBTreeBenchmark/RBTreeTopDownInsert/1048576  631957616 ns  631926010 ns          1

-------------------------------------------------------------------------
Benchmark                                  Time           CPU Iterations
-------------------------------------------------------------------------
RBTreeBenchmark/STLInsert/1024         85021 ns      85067 ns       7972
RBTreeBenchmark/STLInsert/4096        418143 ns     418200 ns       1695
RBTreeBenchmark/STLInsert/16384      2477317 ns    2477415 ns        281
RBTreeBenchmark/STLInsert/65536     13931456 ns   13931396 ns         52
RBTreeBenchmark/STLInsert/262144   114132865 ns  114131050 ns          7
RBTreeBenchmark/STLInsert/1048576  711353579 ns  711338581 ns          1

----------------------------------------------------------------------------
Benchmark                                     Time           CPU Iterations
----------------------------------------------------------------------------
RBTreeBenchmark/RBTreeDelete/1024         81438 ns      81429 ns       8607
RBTreeBenchmark/RBTreeDelete/4096        377786 ns     377772 ns       1852
RBTreeBenchmark/RBTreeDelete/16384      2011234 ns    2011053 ns        348
RBTreeBenchmark/RBTreeDelete/65536     10980907 ns   10980336 ns         64
RBTreeBenchmark/RBTreeDelete/262144    76479309 ns   76477023 ns         10
RBTreeBenchmark/RBTreeDelete/1048576  580648762 ns  580624632 ns          1

------------------------------------------------------------------------------------
Benchmark                                             Time           CPU Iterations
------------------------------------------------------------------------------------
RBTreeBenchmark/RBTreeBottomUpDelete/1024         74750 ns      74736 ns       9386
RBTreeBenchmark/RBTreeBottomUpDelete/4096        356525 ns     356500 ns       1957
RBTreeBenchmark/RBTreeBottomUpDelete/16384      2089264 ns    2089176 ns        334
RBTreeBenchmark/RBTreeBottomUpDelete/65536     11683456 ns   11682752 ns         61
RBTreeBenchmark/RBTreeBottomUpDelete/262144    71483814 ns   71481991 ns          8
RBTreeBenchmark/RBTreeBottomUpDelete/1048576  575147768 ns  575136699 ns          1

-----------------------------------------------------------------------------------
Benchmark                                            Time           CPU Iterations
-----------------------------------------------------------------------------------
RBTreeBenchmark/RBTreeTopDownDelete/1024         88195 ns      88164 ns       7994
RBTreeBenchmark/RBTreeTopDownDelete/4096        430512 ns     430445 ns       1636
RBTreeBenchmark/RBTreeTopDownDelete/16384      2544873 ns    2544812 ns        277
RBTreeBenchmark/RBTreeTopDownDelete/65536     13653508 ns   13653181 ns         50
RBTreeBenchmark/RBTreeTopDownDelete/262144    79422966 ns   79419783 ns          9
RBTreeBenchmark/RBTreeTopDownDelete/1048576  617488191 ns  617424268 ns          1

-------------------------------------------------------------------------
Benchmark                                  Time           CPU Iterations
-------------------------------------------------------------------------
RBTreeBenchmark/STLDelete/1024         76720 ns      76719 ns       9122
RBTreeBenchmark/STLDelete/4096        382207 ns     382188 ns       1835
RBTreeBenchmark/STLDelete/16384      2266140 ns    2266061 ns        311
RBTreeBenchmark/STLDelete/65536     11846670 ns   11845896 ns         60
RBTreeBenchmark/STLDelete/262144    88455988 ns   88453431 ns          7
RBTreeBenchmark/STLDelete/1048576  656733084 ns  656650901 ns          1
</pre>
