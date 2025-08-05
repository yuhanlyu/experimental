## Red-black tree
[Red-black tree](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree) is self-balancing binary search
tree. The operations of insertion and deletion can be done in O(lg n) time in
worst case.

This module implements three versions of insertion/deletion:
1. Iterative Standard algorithm: This is the method discussed in most textbooks, originating from
   [Updating a balanced search tree in O(1) rotations](https://doi.org/10.1016/0020-0190(83)90099-6)
1. Iterative Standard algorithm, but use array of pointer instead of left/right pointers:
   Lin Chen, Rene Schott
   [Optimal operations on red-black trees](https://doi.org/10.1109/ICCI.1993.315316) 
   Moreover, when deleting a node with two children, instead of picking successor/predecessor
   deterministically, the algorithm pick successor or predecessor alternatively.
   The idea is from the following paper.
   Jeffrey L. Eppinger
   [An empirical study of insertion and deletion in binary search trees](https://doi.org/10.1145/358172.358183)
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
-------------------------------------------------------------------------------------------
Benchmark                                                 Time             CPU   Iterations
-------------------------------------------------------------------------------------------
RBTreeBenchmark/RBTreeStandardInsert/1024             74631 ns        73092 ns       652464
RBTreeBenchmark/RBTreeStandardInsert/4096            333235 ns       333249 ns       124432
RBTreeBenchmark/RBTreeStandardInsert/16384          1623105 ns      1623147 ns        25947
RBTreeBenchmark/RBTreeStandardInsert/65536          8796457 ns      8796626 ns         4878
RBTreeBenchmark/RBTreeStandardInsert/262144        63070361 ns     63071789 ns          657
RBTreeBenchmark/RBTreeStandardInsert/1048576      639726737 ns    639727855 ns           66
RBTreeBenchmark/RBTreeStandardLinkInsert/1024         75770 ns        75769 ns       587827
RBTreeBenchmark/RBTreeStandardLinkInsert/4096        412086 ns       412347 ns       103636
RBTreeBenchmark/RBTreeStandardLinkInsert/16384      2420328 ns      2420845 ns        17112
RBTreeBenchmark/RBTreeStandardLinkInsert/65536     14973078 ns     14974375 ns         2798
RBTreeBenchmark/RBTreeStandardLinkInsert/262144   109148882 ns    109150256 ns          384
RBTreeBenchmark/RBTreeStandardLinkInsert/1048576  645713220 ns    645714379 ns           65
RBTreeBenchmark/RBTreeInsert/1024                     97780 ns        97757 ns       429007
RBTreeBenchmark/RBTreeInsert/4096                    467984 ns       468004 ns        89984
RBTreeBenchmark/RBTreeInsert/16384                  2377889 ns      2377904 ns        17487
RBTreeBenchmark/RBTreeInsert/65536                 13031469 ns     13031632 ns         3183
RBTreeBenchmark/RBTreeInsert/262144                74827244 ns     74828476 ns          565
RBTreeBenchmark/RBTreeInsert/1048576              835362815 ns    835364231 ns           52
RBTreeBenchmark/RBTreeBottomUpInsert/1024            117030 ns       117025 ns       356629
RBTreeBenchmark/RBTreeBottomUpInsert/4096            639521 ns       639792 ns        66773
RBTreeBenchmark/RBTreeBottomUpInsert/16384          3976116 ns      3976653 ns        10545
RBTreeBenchmark/RBTreeBottomUpInsert/65536         25302942 ns     25304425 ns         1686
RBTreeBenchmark/RBTreeBottomUpInsert/262144       166152183 ns    166153684 ns          250
RBTreeBenchmark/RBTreeBottomUpInsert/1048576      959592816 ns    959594510 ns           39
RBTreeBenchmark/RBTreeTopDownInsert/1024             111278 ns       111272 ns       367468
RBTreeBenchmark/RBTreeTopDownInsert/4096             612407 ns       612707 ns        68195
RBTreeBenchmark/RBTreeTopDownInsert/16384           3685383 ns      3685960 ns        11361
RBTreeBenchmark/RBTreeTopDownInsert/65536          22755265 ns     22756852 ns         1884
RBTreeBenchmark/RBTreeTopDownInsert/262144        148310694 ns    148312364 ns          283
RBTreeBenchmark/RBTreeTopDownInsert/1048576       850948575 ns    850950006 ns           50
RBTreeBenchmark/STLInsert/1024                        86034 ns        86018 ns       495328
RBTreeBenchmark/STLInsert/4096                       401758 ns       401767 ns       105499
RBTreeBenchmark/STLInsert/16384                     1916101 ns      1916140 ns        21163
RBTreeBenchmark/STLInsert/65536                    10551757 ns     10551960 ns         4081
RBTreeBenchmark/STLInsert/262144                   75032007 ns     75033617 ns          555
RBTreeBenchmark/STLInsert/1048576                 708375383 ns    708376591 ns           59
RBTreeBenchmark/RBTreeStandardDelete/1024             73953 ns        73910 ns       569732
RBTreeBenchmark/RBTreeStandardDelete/4096            392972 ns       392990 ns       105494
RBTreeBenchmark/RBTreeStandardDelete/16384          2432255 ns      2432227 ns        17279
RBTreeBenchmark/RBTreeStandardDelete/65536         14864472 ns     14864725 ns         2844
RBTreeBenchmark/RBTreeStandardDelete/262144        98186265 ns     98186427 ns          426
RBTreeBenchmark/RBTreeStandardDelete/1048576      584388849 ns    584389096 ns           72
RBTreeBenchmark/RBTreeStandardLinkDelete/1024         91452 ns        91413 ns       581901
RBTreeBenchmark/RBTreeStandardLinkDelete/4096        399967 ns       399990 ns       104213
RBTreeBenchmark/RBTreeStandardLinkDelete/16384      2433294 ns      2433261 ns        17432
RBTreeBenchmark/RBTreeStandardLinkDelete/65536     14589765 ns     14590015 ns         2816
RBTreeBenchmark/RBTreeStandardLinkDelete/262144    96276637 ns     96276805 ns          443
RBTreeBenchmark/RBTreeStandardLinkDelete/1048576  578223898 ns    578224160 ns           71
RBTreeBenchmark/RBTreeDelete/1024                     55457 ns        55406 ns       724003
RBTreeBenchmark/RBTreeDelete/4096                    257255 ns       257222 ns       163372
RBTreeBenchmark/RBTreeDelete/16384                  1355928 ns      1355921 ns        30759
RBTreeBenchmark/RBTreeDelete/65536                  7951472 ns      7951489 ns         5334
RBTreeBenchmark/RBTreeDelete/262144                49431266 ns     49431392 ns          849
RBTreeBenchmark/RBTreeDelete/1048576              665562943 ns    665563105 ns           64
RBTreeBenchmark/RBTreeBottomUpDelete/1024             95262 ns        95222 ns       448296
RBTreeBenchmark/RBTreeBottomUpDelete/4096            536241 ns       536237 ns        77925
RBTreeBenchmark/RBTreeBottomUpDelete/16384          3217989 ns      3217842 ns        13064
RBTreeBenchmark/RBTreeBottomUpDelete/65536         20207984 ns     20208132 ns         2095
RBTreeBenchmark/RBTreeBottomUpDelete/262144       135955343 ns    135955386 ns          298
RBTreeBenchmark/RBTreeBottomUpDelete/1048576      815742593 ns    815742750 ns           51
RBTreeBenchmark/RBTreeTopDownDelete/1024              99191 ns        99147 ns       425521
RBTreeBenchmark/RBTreeTopDownDelete/4096             561697 ns       564065 ns        65079
RBTreeBenchmark/RBTreeTopDownDelete/16384           3391422 ns      3391271 ns        12468
RBTreeBenchmark/RBTreeTopDownDelete/65536          19799482 ns     19799590 ns         2123
RBTreeBenchmark/RBTreeTopDownDelete/262144        122462116 ns    122462161 ns          344
RBTreeBenchmark/RBTreeTopDownDelete/1048576       742253221 ns    742253269 ns           57
RBTreeBenchmark/STLDelete/1024                        83873 ns        83833 ns       503342
RBTreeBenchmark/STLDelete/4096                       406591 ns       406570 ns       102636
RBTreeBenchmark/STLDelete/16384                     2168357 ns      2168367 ns        19466
RBTreeBenchmark/STLDelete/65536                    12341731 ns     12341714 ns         3358
RBTreeBenchmark/STLDelete/262144                   88210042 ns     88210110 ns          476
RBTreeBenchmark/STLDelete/1048576                 803348379 ns    803348558 ns           53
RBTreeBenchmark/RBTreeStandardMix/1024                18563 ns        18539 ns      2266475
RBTreeBenchmark/RBTreeStandardMix/4096                93182 ns        93141 ns       451160
RBTreeBenchmark/RBTreeStandardMix/16384              491380 ns       491358 ns        86645
RBTreeBenchmark/RBTreeStandardMix/65536             2787515 ns      2787401 ns        15125
RBTreeBenchmark/RBTreeStandardMix/262144           19368585 ns     19368679 ns         2185
RBTreeBenchmark/RBTreeStandardMix/1048576          83299715 ns     83299502 ns          506
RBTreeBenchmark/RBTreeStandardLinkMix/1024            18313 ns        18280 ns      2302488
RBTreeBenchmark/RBTreeStandardLinkMix/4096            92140 ns        92094 ns       440049
RBTreeBenchmark/RBTreeStandardLinkMix/16384          489642 ns       489621 ns        86229
RBTreeBenchmark/RBTreeStandardLinkMix/65536         2770016 ns      2769937 ns        15018
RBTreeBenchmark/RBTreeStandardLinkMix/262144       19536634 ns     19536691 ns         2156
RBTreeBenchmark/RBTreeStandardLinkMix/1048576      83847885 ns     83847760 ns          496
RBTreeBenchmark/RBTreeMix/1024                        16023 ns        15979 ns      2644875
RBTreeBenchmark/RBTreeMix/4096                        61686 ns        61656 ns       666479
RBTreeBenchmark/RBTreeMix/16384                      251666 ns       251635 ns       166733
RBTreeBenchmark/RBTreeMix/65536                     1193502 ns      1193501 ns        35705
RBTreeBenchmark/RBTreeMix/262144                    6490029 ns      6489768 ns         6664
RBTreeBenchmark/RBTreeMix/1048576                  73392510 ns     73392390 ns          566
RBTreeBenchmark/RBTreeBottomUpMix/1024                19009 ns        18987 ns      2217189
RBTreeBenchmark/RBTreeBottomUpMix/4096                90273 ns        90196 ns       462196
RBTreeBenchmark/RBTreeBottomUpMix/16384              469390 ns       469300 ns        89115
RBTreeBenchmark/RBTreeBottomUpMix/65536             2523046 ns      2523007 ns        16703
RBTreeBenchmark/RBTreeBottomUpMix/262144           17306049 ns     17306149 ns         2442
RBTreeBenchmark/RBTreeBottomUpMix/1048576          73673442 ns     73673331 ns          578
RBTreeBenchmark/RBTreeTopDownMix/1024                 19166 ns        19141 ns      2177675
RBTreeBenchmark/RBTreeTopDownMix/4096                 90036 ns        89925 ns       463718
RBTreeBenchmark/RBTreeTopDownMix/16384               472681 ns       472593 ns        89979
RBTreeBenchmark/RBTreeTopDownMix/65536              2584301 ns      2584139 ns        16436
RBTreeBenchmark/RBTreeTopDownMix/262144            17407450 ns     17407498 ns         2455
RBTreeBenchmark/RBTreeTopDownMix/1048576           74699975 ns     74699809 ns          567
RBTreeBenchmark/RBTreeSTLMix/1024                     16732 ns        16701 ns      2546535
RBTreeBenchmark/RBTreeSTLMix/4096                     63268 ns        63242 ns       655283
RBTreeBenchmark/RBTreeSTLMix/16384                   254030 ns       254012 ns       165925
RBTreeBenchmark/RBTreeSTLMix/65536                  1277903 ns      1277905 ns        32885
RBTreeBenchmark/RBTreeSTLMix/262144                 9988206 ns      9988192 ns         4204
RBTreeBenchmark/RBTreeSTLMix/1048576               88473548 ns     88473415 ns          478
</pre>
