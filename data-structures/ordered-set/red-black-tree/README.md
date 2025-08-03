## Red-black tree
[Red-black tree](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree) is self-balancing binary search
tree. The operations of insertion and deletion can be done in O(lg n) time in
worst case.

This module implements three versions of insertion/deletion:
1. Iterative Standard algorithm: This is the method discussed in most textbooks, originating from
   [Updating a balanced search tree in O(1) rotations](https://doi.org/10.1016/0020-0190(83)90099-6)
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
iterative method uses only one pass and constant space, the number of rotations
is Ω(lg n) even in the amortized case.

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
one pass, 8 levels lookahead in insertion and 4 levels lookahead in deletion
are required.

## Benchmark
<pre>
RBTreeBenchmark/RBTreeStandardInsert/1048576                625681737 ns    625674261 ns           66
RBTreeBenchmark/RBTreeInsert/1048576                        751765798 ns    751756309 ns           56
RBTreeBenchmark/RBTreeBottomUpInsert/1048576                908580650 ns    908570615 ns           46
RBTreeBenchmark/RBTreeTopDownInsert/1048576                 809661853 ns    809653314 ns           53
RBTreeBenchmark/STLInsert/1048576                           682002263 ns    681993340 ns           62
RBTreeBenchmark/RBTreeStandardDelete/1048576                545968168 ns    545959250 ns           77
RBTreeBenchmark/RBTreeDelete/1048576                        660281126 ns    660269545 ns           64
RBTreeBenchmark/RBTreeBottomUpDelete/1048576                832234530 ns    832219334 ns           51
RBTreeBenchmark/RBTreeTopDownDelete/1048576                 772958214 ns    772942769 ns           55
RBTreeBenchmark/STLDelete/1048576                           781583089 ns    781568875 ns           53
</pre>
