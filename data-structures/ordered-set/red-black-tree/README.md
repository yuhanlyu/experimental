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
--------------------------------------------------------------------------------------------------
Benchmark                                                        Time             CPU   Iterations
--------------------------------------------------------------------------------------------------
RBTreeBenchmark/RBTreeStandardInsert/1024_mean                3446 ns         3420 ns          100
RBTreeBenchmark/RBTreeStandardInsert/1024_median              3488 ns         3459 ns          100
RBTreeBenchmark/RBTreeStandardInsert/1024_stddev               129 ns          128 ns          100
RBTreeBenchmark/RBTreeStandardInsert/1024_cv                  3.76 %          3.73 %           100
RBTreeBenchmark/RBTreeStandardInsert/4096_mean                3877 ns         3868 ns          100
RBTreeBenchmark/RBTreeStandardInsert/4096_median              3881 ns         3872 ns          100
RBTreeBenchmark/RBTreeStandardInsert/4096_stddev              79.9 ns         80.4 ns          100
RBTreeBenchmark/RBTreeStandardInsert/4096_cv                  2.06 %          2.08 %           100
RBTreeBenchmark/RBTreeStandardInsert/16384_mean               4303 ns         4296 ns          100
RBTreeBenchmark/RBTreeStandardInsert/16384_median             4300 ns         4292 ns          100
RBTreeBenchmark/RBTreeStandardInsert/16384_stddev             92.9 ns         94.3 ns          100
RBTreeBenchmark/RBTreeStandardInsert/16384_cv                 2.16 %          2.20 %           100
RBTreeBenchmark/RBTreeStandardInsert/65536_mean               5124 ns         5118 ns          100
RBTreeBenchmark/RBTreeStandardInsert/65536_median             4931 ns         4927 ns          100
RBTreeBenchmark/RBTreeStandardInsert/65536_stddev              548 ns          550 ns          100
RBTreeBenchmark/RBTreeStandardInsert/65536_cv                10.70 %         10.74 %           100
RBTreeBenchmark/RBTreeStandardInsert/262144_mean              6685 ns         6689 ns          100
RBTreeBenchmark/RBTreeStandardInsert/262144_median            6678 ns         6685 ns          100
RBTreeBenchmark/RBTreeStandardInsert/262144_stddev             107 ns          109 ns          100
RBTreeBenchmark/RBTreeStandardInsert/262144_cv                1.60 %          1.63 %           100
RBTreeBenchmark/RBTreeStandardInsert/1048576_mean             9153 ns         9158 ns          100
RBTreeBenchmark/RBTreeStandardInsert/1048576_median           9114 ns         9126 ns          100
RBTreeBenchmark/RBTreeStandardInsert/1048576_stddev            210 ns          211 ns          100
RBTreeBenchmark/RBTreeStandardInsert/1048576_cv               2.29 %          2.30 %           100
RBTreeBenchmark/RBTreeStandardInsert/4194304_mean            12191 ns        12199 ns          100
RBTreeBenchmark/RBTreeStandardInsert/4194304_median          12154 ns        12158 ns          100
RBTreeBenchmark/RBTreeStandardInsert/4194304_stddev            331 ns          333 ns          100
RBTreeBenchmark/RBTreeStandardInsert/4194304_cv               2.71 %          2.73 %           100
RBTreeBenchmark/RBTreeStandardLinkInsert/1024_mean            3866 ns         3849 ns          100
RBTreeBenchmark/RBTreeStandardLinkInsert/1024_median          3820 ns         3809 ns          100
RBTreeBenchmark/RBTreeStandardLinkInsert/1024_stddev           287 ns          285 ns          100
RBTreeBenchmark/RBTreeStandardLinkInsert/1024_cv              7.42 %          7.40 %           100
RBTreeBenchmark/RBTreeStandardLinkInsert/4096_mean            4055 ns         4043 ns          100
RBTreeBenchmark/RBTreeStandardLinkInsert/4096_median          4050 ns         4040 ns          100
RBTreeBenchmark/RBTreeStandardLinkInsert/4096_stddev          66.6 ns         65.4 ns          100
RBTreeBenchmark/RBTreeStandardLinkInsert/4096_cv              1.64 %          1.62 %           100
RBTreeBenchmark/RBTreeStandardLinkInsert/16384_mean           4334 ns         4323 ns          100
RBTreeBenchmark/RBTreeStandardLinkInsert/16384_median         4326 ns         4319 ns          100
RBTreeBenchmark/RBTreeStandardLinkInsert/16384_stddev         80.3 ns         80.0 ns          100
RBTreeBenchmark/RBTreeStandardLinkInsert/16384_cv             1.85 %          1.85 %           100
RBTreeBenchmark/RBTreeStandardLinkInsert/65536_mean           5010 ns         4997 ns          100
RBTreeBenchmark/RBTreeStandardLinkInsert/65536_median         4988 ns         4975 ns          100
RBTreeBenchmark/RBTreeStandardLinkInsert/65536_stddev          171 ns          172 ns          100
RBTreeBenchmark/RBTreeStandardLinkInsert/65536_cv             3.42 %          3.44 %           100
RBTreeBenchmark/RBTreeStandardLinkInsert/262144_mean          6471 ns         6458 ns          100
RBTreeBenchmark/RBTreeStandardLinkInsert/262144_median        6455 ns         6444 ns          100
RBTreeBenchmark/RBTreeStandardLinkInsert/262144_stddev         119 ns          119 ns          100
RBTreeBenchmark/RBTreeStandardLinkInsert/262144_cv            1.84 %          1.85 %           100
RBTreeBenchmark/RBTreeStandardLinkInsert/1048576_mean         8884 ns         8875 ns          100
RBTreeBenchmark/RBTreeStandardLinkInsert/1048576_median       8888 ns         8879 ns          100
RBTreeBenchmark/RBTreeStandardLinkInsert/1048576_stddev        193 ns          196 ns          100
RBTreeBenchmark/RBTreeStandardLinkInsert/1048576_cv           2.17 %          2.21 %           100
RBTreeBenchmark/RBTreeStandardLinkInsert/4194304_mean        11874 ns        11867 ns          100
RBTreeBenchmark/RBTreeStandardLinkInsert/4194304_median      11877 ns        11875 ns          100
RBTreeBenchmark/RBTreeStandardLinkInsert/4194304_stddev        197 ns          197 ns          100
RBTreeBenchmark/RBTreeStandardLinkInsert/4194304_cv           1.66 %          1.66 %           100
RBTreeBenchmark/RBTreeInsert/1024_mean                        4233 ns         4204 ns          100
RBTreeBenchmark/RBTreeInsert/1024_median                      4212 ns         4181 ns          100
RBTreeBenchmark/RBTreeInsert/1024_stddev                       109 ns          111 ns          100
RBTreeBenchmark/RBTreeInsert/1024_cv                          2.57 %          2.64 %           100
RBTreeBenchmark/RBTreeInsert/4096_mean                        4729 ns         4711 ns          100
RBTreeBenchmark/RBTreeInsert/4096_median                      4726 ns         4707 ns          100
RBTreeBenchmark/RBTreeInsert/4096_stddev                      99.1 ns         96.5 ns          100
RBTreeBenchmark/RBTreeInsert/4096_cv                          2.10 %          2.05 %           100
RBTreeBenchmark/RBTreeInsert/16384_mean                       5363 ns         5348 ns          100
RBTreeBenchmark/RBTreeInsert/16384_median                     5368 ns         5350 ns          100
RBTreeBenchmark/RBTreeInsert/16384_stddev                      120 ns          119 ns          100
RBTreeBenchmark/RBTreeInsert/16384_cv                         2.23 %          2.23 %           100
RBTreeBenchmark/RBTreeInsert/65536_mean                       6624 ns         6614 ns          100
RBTreeBenchmark/RBTreeInsert/65536_median                     6632 ns         6622 ns          100
RBTreeBenchmark/RBTreeInsert/65536_stddev                      119 ns          120 ns          100
RBTreeBenchmark/RBTreeInsert/65536_cv                         1.79 %          1.82 %           100
RBTreeBenchmark/RBTreeInsert/262144_mean                     10512 ns        10507 ns          100
RBTreeBenchmark/RBTreeInsert/262144_median                   10463 ns        10458 ns          100
RBTreeBenchmark/RBTreeInsert/262144_stddev                     377 ns          378 ns          100
RBTreeBenchmark/RBTreeInsert/262144_cv                        3.58 %          3.60 %           100
RBTreeBenchmark/RBTreeInsert/1048576_mean                    15020 ns        15024 ns          100
RBTreeBenchmark/RBTreeInsert/1048576_median                  14990 ns        14994 ns          100
RBTreeBenchmark/RBTreeInsert/1048576_stddev                    356 ns          359 ns          100
RBTreeBenchmark/RBTreeInsert/1048576_cv                       2.37 %          2.39 %           100
RBTreeBenchmark/RBTreeInsert/4194304_mean                    20238 ns        20256 ns          100
RBTreeBenchmark/RBTreeInsert/4194304_median                  20167 ns        20197 ns          100
RBTreeBenchmark/RBTreeInsert/4194304_stddev                    634 ns          636 ns          100
RBTreeBenchmark/RBTreeInsert/4194304_cv                       3.13 %          3.14 %           100
RBTreeBenchmark/RBTreeBottomUpInsert/1024_mean                4175 ns         4152 ns          100
RBTreeBenchmark/RBTreeBottomUpInsert/1024_median              4172 ns         4151 ns          100
RBTreeBenchmark/RBTreeBottomUpInsert/1024_stddev              69.0 ns         70.9 ns          100
RBTreeBenchmark/RBTreeBottomUpInsert/1024_cv                  1.65 %          1.71 %           100
RBTreeBenchmark/RBTreeBottomUpInsert/4096_mean                4580 ns         4559 ns          100
RBTreeBenchmark/RBTreeBottomUpInsert/4096_median              4569 ns         4549 ns          100
RBTreeBenchmark/RBTreeBottomUpInsert/4096_stddev               105 ns          106 ns          100
RBTreeBenchmark/RBTreeBottomUpInsert/4096_cv                  2.30 %          2.32 %           100
RBTreeBenchmark/RBTreeBottomUpInsert/16384_mean               5134 ns         5121 ns          100
RBTreeBenchmark/RBTreeBottomUpInsert/16384_median             5146 ns         5136 ns          100
RBTreeBenchmark/RBTreeBottomUpInsert/16384_stddev              151 ns          152 ns          100
RBTreeBenchmark/RBTreeBottomUpInsert/16384_cv                 2.94 %          2.96 %           100
RBTreeBenchmark/RBTreeBottomUpInsert/65536_mean               6220 ns         6211 ns          100
RBTreeBenchmark/RBTreeBottomUpInsert/65536_median             6262 ns         6249 ns          100
RBTreeBenchmark/RBTreeBottomUpInsert/65536_stddev              208 ns          209 ns          100
RBTreeBenchmark/RBTreeBottomUpInsert/65536_cv                 3.34 %          3.37 %           100
RBTreeBenchmark/RBTreeBottomUpInsert/262144_mean              9740 ns         9739 ns          100
RBTreeBenchmark/RBTreeBottomUpInsert/262144_median            9859 ns         9849 ns          100
RBTreeBenchmark/RBTreeBottomUpInsert/262144_stddev             381 ns          383 ns          100
RBTreeBenchmark/RBTreeBottomUpInsert/262144_cv                3.91 %          3.93 %           100
RBTreeBenchmark/RBTreeBottomUpInsert/1048576_mean            13651 ns        13655 ns          100
RBTreeBenchmark/RBTreeBottomUpInsert/1048576_median          13589 ns        13584 ns          100
RBTreeBenchmark/RBTreeBottomUpInsert/1048576_stddev            382 ns          383 ns          100
RBTreeBenchmark/RBTreeBottomUpInsert/1048576_cv               2.80 %          2.80 %           100
RBTreeBenchmark/RBTreeBottomUpInsert/4194304_mean            19056 ns        19064 ns          100
RBTreeBenchmark/RBTreeBottomUpInsert/4194304_median          18966 ns        18973 ns          100
RBTreeBenchmark/RBTreeBottomUpInsert/4194304_stddev            613 ns          615 ns          100
RBTreeBenchmark/RBTreeBottomUpInsert/4194304_cv               3.22 %          3.23 %           100
RBTreeBenchmark/RBTreeTopDownInsert/1024_mean                 4432 ns         4414 ns          100
RBTreeBenchmark/RBTreeTopDownInsert/1024_median               4428 ns         4414 ns          100
RBTreeBenchmark/RBTreeTopDownInsert/1024_stddev                116 ns          116 ns          100
RBTreeBenchmark/RBTreeTopDownInsert/1024_cv                   2.61 %          2.64 %           100
RBTreeBenchmark/RBTreeTopDownInsert/4096_mean                 5049 ns         5040 ns          100
RBTreeBenchmark/RBTreeTopDownInsert/4096_median               5051 ns         5043 ns          100
RBTreeBenchmark/RBTreeTopDownInsert/4096_stddev               87.7 ns         90.4 ns          100
RBTreeBenchmark/RBTreeTopDownInsert/4096_cv                   1.74 %          1.79 %           100
RBTreeBenchmark/RBTreeTopDownInsert/16384_mean                5761 ns         5754 ns          100
RBTreeBenchmark/RBTreeTopDownInsert/16384_median              5753 ns         5752 ns          100
RBTreeBenchmark/RBTreeTopDownInsert/16384_stddev               138 ns          141 ns          100
RBTreeBenchmark/RBTreeTopDownInsert/16384_cv                  2.40 %          2.44 %           100
RBTreeBenchmark/RBTreeTopDownInsert/65536_mean                7054 ns         7064 ns          100
RBTreeBenchmark/RBTreeTopDownInsert/65536_median              7031 ns         7037 ns          100
RBTreeBenchmark/RBTreeTopDownInsert/65536_stddev               220 ns          223 ns          100
RBTreeBenchmark/RBTreeTopDownInsert/65536_cv                  3.12 %          3.15 %           100
RBTreeBenchmark/RBTreeTopDownInsert/262144_mean              10993 ns        11006 ns          100
RBTreeBenchmark/RBTreeTopDownInsert/262144_median            10993 ns        11007 ns          100
RBTreeBenchmark/RBTreeTopDownInsert/262144_stddev              220 ns          222 ns          100
RBTreeBenchmark/RBTreeTopDownInsert/262144_cv                 2.00 %          2.01 %           100
RBTreeBenchmark/RBTreeTopDownInsert/1048576_mean             15771 ns        15793 ns          100
RBTreeBenchmark/RBTreeTopDownInsert/1048576_median           15763 ns        15794 ns          100
RBTreeBenchmark/RBTreeTopDownInsert/1048576_stddev             383 ns          384 ns          100
RBTreeBenchmark/RBTreeTopDownInsert/1048576_cv                2.43 %          2.43 %           100
RBTreeBenchmark/RBTreeTopDownInsert/4194304_mean             21266 ns        21299 ns          100
RBTreeBenchmark/RBTreeTopDownInsert/4194304_median           21244 ns        21276 ns          100
RBTreeBenchmark/RBTreeTopDownInsert/4194304_stddev             484 ns          487 ns          100
RBTreeBenchmark/RBTreeTopDownInsert/4194304_cv                2.28 %          2.29 %           100
RBTreeBenchmark/RBTreeSTLInsert/1024_mean                     3744 ns         3710 ns          100
RBTreeBenchmark/RBTreeSTLInsert/1024_median                   3734 ns         3700 ns          100
RBTreeBenchmark/RBTreeSTLInsert/1024_stddev                    108 ns          108 ns          100
RBTreeBenchmark/RBTreeSTLInsert/1024_cv                       2.88 %          2.90 %           100
RBTreeBenchmark/RBTreeSTLInsert/4096_mean                     4039 ns         4016 ns          100
RBTreeBenchmark/RBTreeSTLInsert/4096_median                   4032 ns         4008 ns          100
RBTreeBenchmark/RBTreeSTLInsert/4096_stddev                   97.3 ns         95.5 ns          100
RBTreeBenchmark/RBTreeSTLInsert/4096_cv                       2.41 %          2.38 %           100
RBTreeBenchmark/RBTreeSTLInsert/16384_mean                    4478 ns         4461 ns          100
RBTreeBenchmark/RBTreeSTLInsert/16384_median                  4474 ns         4457 ns          100
RBTreeBenchmark/RBTreeSTLInsert/16384_stddev                   129 ns          130 ns          100
RBTreeBenchmark/RBTreeSTLInsert/16384_cv                      2.88 %          2.91 %           100
RBTreeBenchmark/RBTreeSTLInsert/65536_mean                    5126 ns         5120 ns          100
RBTreeBenchmark/RBTreeSTLInsert/65536_median                  5137 ns         5131 ns          100
RBTreeBenchmark/RBTreeSTLInsert/65536_stddev                   127 ns          127 ns          100
RBTreeBenchmark/RBTreeSTLInsert/65536_cv                      2.48 %          2.48 %           100
RBTreeBenchmark/RBTreeSTLInsert/262144_mean                   7910 ns         7910 ns          100
RBTreeBenchmark/RBTreeSTLInsert/262144_median                 7971 ns         7976 ns          100
RBTreeBenchmark/RBTreeSTLInsert/262144_stddev                  294 ns          296 ns          100
RBTreeBenchmark/RBTreeSTLInsert/262144_cv                     3.72 %          3.75 %           100
RBTreeBenchmark/RBTreeSTLInsert/1048576_mean                 14338 ns        14346 ns          100
RBTreeBenchmark/RBTreeSTLInsert/1048576_median               14395 ns        14401 ns          100
RBTreeBenchmark/RBTreeSTLInsert/1048576_stddev                 576 ns          581 ns          100
RBTreeBenchmark/RBTreeSTLInsert/1048576_cv                    4.02 %          4.05 %           100
RBTreeBenchmark/RBTreeSTLInsert/4194304_mean                 20611 ns        20628 ns          100
RBTreeBenchmark/RBTreeSTLInsert/4194304_median               20382 ns        20396 ns          100
RBTreeBenchmark/RBTreeSTLInsert/4194304_stddev                2155 ns         2160 ns          100
RBTreeBenchmark/RBTreeSTLInsert/4194304_cv                   10.46 %         10.47 %           100
RBTreeBenchmark/RBTreeStandardDelete/1024_mean                3171 ns         3143 ns          100
RBTreeBenchmark/RBTreeStandardDelete/1024_median              3167 ns         3140 ns          100
RBTreeBenchmark/RBTreeStandardDelete/1024_stddev              68.7 ns         68.8 ns          100
RBTreeBenchmark/RBTreeStandardDelete/1024_cv                  2.17 %          2.19 %           100
RBTreeBenchmark/RBTreeStandardDelete/4096_mean                3184 ns         3157 ns          100
RBTreeBenchmark/RBTreeStandardDelete/4096_median              3177 ns         3151 ns          100
RBTreeBenchmark/RBTreeStandardDelete/4096_stddev              67.6 ns         67.3 ns          100
RBTreeBenchmark/RBTreeStandardDelete/4096_cv                  2.12 %          2.13 %           100
RBTreeBenchmark/RBTreeStandardDelete/16384_mean               3170 ns         3145 ns          100
RBTreeBenchmark/RBTreeStandardDelete/16384_median             3167 ns         3142 ns          100
RBTreeBenchmark/RBTreeStandardDelete/16384_stddev             70.7 ns         70.3 ns          100
RBTreeBenchmark/RBTreeStandardDelete/16384_cv                 2.23 %          2.24 %           100
RBTreeBenchmark/RBTreeStandardDelete/65536_mean               3391 ns         3368 ns          100
RBTreeBenchmark/RBTreeStandardDelete/65536_median             3391 ns         3368 ns          100
RBTreeBenchmark/RBTreeStandardDelete/65536_stddev             60.3 ns         60.2 ns          100
RBTreeBenchmark/RBTreeStandardDelete/65536_cv                 1.78 %          1.79 %           100
RBTreeBenchmark/RBTreeStandardDelete/262144_mean              6667 ns         6664 ns          100
RBTreeBenchmark/RBTreeStandardDelete/262144_median            6677 ns         6670 ns          100
RBTreeBenchmark/RBTreeStandardDelete/262144_stddev             145 ns          146 ns          100
RBTreeBenchmark/RBTreeStandardDelete/262144_cv                2.17 %          2.19 %           100
RBTreeBenchmark/RBTreeStandardDelete/1048576_mean            15053 ns        15063 ns          100
RBTreeBenchmark/RBTreeStandardDelete/1048576_median          14901 ns        14911 ns          100
RBTreeBenchmark/RBTreeStandardDelete/1048576_stddev            635 ns          635 ns          100
RBTreeBenchmark/RBTreeStandardDelete/1048576_cv               4.22 %          4.21 %           100
RBTreeBenchmark/RBTreeStandardDelete/4194304_mean            21358 ns        21375 ns          100
RBTreeBenchmark/RBTreeStandardDelete/4194304_median          20982 ns        20996 ns          100
RBTreeBenchmark/RBTreeStandardDelete/4194304_stddev           1635 ns         1640 ns          100
RBTreeBenchmark/RBTreeStandardDelete/4194304_cv               7.66 %          7.67 %           100
RBTreeBenchmark/RBTreeStandardLinkDelete/1024_mean            3170 ns         3143 ns          100
RBTreeBenchmark/RBTreeStandardLinkDelete/1024_median          3164 ns         3138 ns          100
RBTreeBenchmark/RBTreeStandardLinkDelete/1024_stddev          58.1 ns         58.4 ns          100
RBTreeBenchmark/RBTreeStandardLinkDelete/1024_cv              1.83 %          1.86 %           100
RBTreeBenchmark/RBTreeStandardLinkDelete/4096_mean            3162 ns         3136 ns          100
RBTreeBenchmark/RBTreeStandardLinkDelete/4096_median          3169 ns         3144 ns          100
RBTreeBenchmark/RBTreeStandardLinkDelete/4096_stddev          67.4 ns         67.5 ns          100
RBTreeBenchmark/RBTreeStandardLinkDelete/4096_cv              2.13 %          2.15 %           100
RBTreeBenchmark/RBTreeStandardLinkDelete/16384_mean           3182 ns         3155 ns          100
RBTreeBenchmark/RBTreeStandardLinkDelete/16384_median         3174 ns         3147 ns          100
RBTreeBenchmark/RBTreeStandardLinkDelete/16384_stddev         59.5 ns         59.4 ns          100
RBTreeBenchmark/RBTreeStandardLinkDelete/16384_cv             1.87 %          1.88 %           100
RBTreeBenchmark/RBTreeStandardLinkDelete/65536_mean           3371 ns         3346 ns          100
RBTreeBenchmark/RBTreeStandardLinkDelete/65536_median         3358 ns         3336 ns          100
RBTreeBenchmark/RBTreeStandardLinkDelete/65536_stddev         89.4 ns         90.3 ns          100
RBTreeBenchmark/RBTreeStandardLinkDelete/65536_cv             2.65 %          2.70 %           100
RBTreeBenchmark/RBTreeStandardLinkDelete/262144_mean          6726 ns         6727 ns          100
RBTreeBenchmark/RBTreeStandardLinkDelete/262144_median        6693 ns         6693 ns          100
RBTreeBenchmark/RBTreeStandardLinkDelete/262144_stddev         246 ns          248 ns          100
RBTreeBenchmark/RBTreeStandardLinkDelete/262144_cv            3.66 %          3.69 %           100
RBTreeBenchmark/RBTreeStandardLinkDelete/1048576_mean        15250 ns        15261 ns          100
RBTreeBenchmark/RBTreeStandardLinkDelete/1048576_median      14944 ns        14947 ns          100
RBTreeBenchmark/RBTreeStandardLinkDelete/1048576_stddev       1273 ns         1274 ns          100
RBTreeBenchmark/RBTreeStandardLinkDelete/1048576_cv           8.34 %          8.35 %           100
RBTreeBenchmark/RBTreeStandardLinkDelete/4194304_mean        21038 ns        21052 ns          100
RBTreeBenchmark/RBTreeStandardLinkDelete/4194304_median      20963 ns        20973 ns          100
RBTreeBenchmark/RBTreeStandardLinkDelete/4194304_stddev        482 ns          484 ns          100
RBTreeBenchmark/RBTreeStandardLinkDelete/4194304_cv           2.29 %          2.30 %           100
RBTreeBenchmark/RBTreeDelete/1024_mean                        3247 ns         3220 ns          100
RBTreeBenchmark/RBTreeDelete/1024_median                      3239 ns         3211 ns          100
RBTreeBenchmark/RBTreeDelete/1024_stddev                      56.4 ns         56.0 ns          100
RBTreeBenchmark/RBTreeDelete/1024_cv                          1.74 %          1.74 %           100
RBTreeBenchmark/RBTreeDelete/4096_mean                        3160 ns         3134 ns          100
RBTreeBenchmark/RBTreeDelete/4096_median                      3154 ns         3129 ns          100
RBTreeBenchmark/RBTreeDelete/4096_stddev                      61.3 ns         61.0 ns          100
RBTreeBenchmark/RBTreeDelete/4096_cv                          1.94 %          1.94 %           100
RBTreeBenchmark/RBTreeDelete/16384_mean                       3215 ns         3190 ns          100
RBTreeBenchmark/RBTreeDelete/16384_median                     3211 ns         3184 ns          100
RBTreeBenchmark/RBTreeDelete/16384_stddev                     58.9 ns         58.7 ns          100
RBTreeBenchmark/RBTreeDelete/16384_cv                         1.83 %          1.84 %           100
RBTreeBenchmark/RBTreeDelete/65536_mean                       3568 ns         3549 ns          100
RBTreeBenchmark/RBTreeDelete/65536_median                     3534 ns         3514 ns          100
RBTreeBenchmark/RBTreeDelete/65536_stddev                      128 ns          129 ns          100
RBTreeBenchmark/RBTreeDelete/65536_cv                         3.58 %          3.63 %           100
RBTreeBenchmark/RBTreeDelete/262144_mean                      8530 ns         8544 ns          100
RBTreeBenchmark/RBTreeDelete/262144_median                    8520 ns         8531 ns          100
RBTreeBenchmark/RBTreeDelete/262144_stddev                     170 ns          171 ns          100
RBTreeBenchmark/RBTreeDelete/262144_cv                        1.99 %          2.01 %           100
RBTreeBenchmark/RBTreeDelete/1048576_mean                    16257 ns        16280 ns          100
RBTreeBenchmark/RBTreeDelete/1048576_median                  16150 ns        16175 ns          100
RBTreeBenchmark/RBTreeDelete/1048576_stddev                    983 ns          982 ns          100
RBTreeBenchmark/RBTreeDelete/1048576_cv                       6.05 %          6.03 %           100
RBTreeBenchmark/RBTreeDelete/4194304_mean                    22676 ns        22705 ns          100
RBTreeBenchmark/RBTreeDelete/4194304_median                  22646 ns        22678 ns          100
RBTreeBenchmark/RBTreeDelete/4194304_stddev                    684 ns          684 ns          100
RBTreeBenchmark/RBTreeDelete/4194304_cv                       3.02 %          3.01 %           100
RBTreeBenchmark/RBTreeBottomUpDelete/1024_mean                3329 ns         3296 ns          100
RBTreeBenchmark/RBTreeBottomUpDelete/1024_median              3322 ns         3286 ns          100
RBTreeBenchmark/RBTreeBottomUpDelete/1024_stddev              66.4 ns         66.3 ns          100
RBTreeBenchmark/RBTreeBottomUpDelete/1024_cv                  1.99 %          2.01 %           100
RBTreeBenchmark/RBTreeBottomUpDelete/4096_mean                3272 ns         3237 ns          100
RBTreeBenchmark/RBTreeBottomUpDelete/4096_median              3259 ns         3225 ns          100
RBTreeBenchmark/RBTreeBottomUpDelete/4096_stddev               103 ns          102 ns          100
RBTreeBenchmark/RBTreeBottomUpDelete/4096_cv                  3.13 %          3.15 %           100
RBTreeBenchmark/RBTreeBottomUpDelete/16384_mean               3321 ns         3286 ns          100
RBTreeBenchmark/RBTreeBottomUpDelete/16384_median             3322 ns         3288 ns          100
RBTreeBenchmark/RBTreeBottomUpDelete/16384_stddev             72.1 ns         71.4 ns          100
RBTreeBenchmark/RBTreeBottomUpDelete/16384_cv                 2.17 %          2.17 %           100
RBTreeBenchmark/RBTreeBottomUpDelete/65536_mean               3703 ns         3672 ns          100
RBTreeBenchmark/RBTreeBottomUpDelete/65536_median             3618 ns         3585 ns          100
RBTreeBenchmark/RBTreeBottomUpDelete/65536_stddev              291 ns          289 ns          100
RBTreeBenchmark/RBTreeBottomUpDelete/65536_cv                 7.85 %          7.86 %           100
RBTreeBenchmark/RBTreeBottomUpDelete/262144_mean              8347 ns         8341 ns          100
RBTreeBenchmark/RBTreeBottomUpDelete/262144_median            8322 ns         8320 ns          100
RBTreeBenchmark/RBTreeBottomUpDelete/262144_stddev             203 ns          202 ns          100
RBTreeBenchmark/RBTreeBottomUpDelete/262144_cv                2.43 %          2.42 %           100
RBTreeBenchmark/RBTreeBottomUpDelete/1048576_mean            16316 ns        16323 ns          100
RBTreeBenchmark/RBTreeBottomUpDelete/1048576_median          16247 ns        16251 ns          100
RBTreeBenchmark/RBTreeBottomUpDelete/1048576_stddev            382 ns          382 ns          100
RBTreeBenchmark/RBTreeBottomUpDelete/1048576_cv               2.34 %          2.34 %           100
RBTreeBenchmark/RBTreeBottomUpDelete/4194304_mean            22350 ns        22357 ns          100
RBTreeBenchmark/RBTreeBottomUpDelete/4194304_median          22225 ns        22227 ns          100
RBTreeBenchmark/RBTreeBottomUpDelete/4194304_stddev           1127 ns         1129 ns          100
RBTreeBenchmark/RBTreeBottomUpDelete/4194304_cv               5.04 %          5.05 %           100
RBTreeBenchmark/RBTreeTopDownDelete/1024_mean                 3273 ns         3245 ns          100
RBTreeBenchmark/RBTreeTopDownDelete/1024_median               3267 ns         3241 ns          100
RBTreeBenchmark/RBTreeTopDownDelete/1024_stddev               66.6 ns         66.4 ns          100
RBTreeBenchmark/RBTreeTopDownDelete/1024_cv                   2.03 %          2.05 %           100
RBTreeBenchmark/RBTreeTopDownDelete/4096_mean                 3233 ns         3206 ns          100
RBTreeBenchmark/RBTreeTopDownDelete/4096_median               3228 ns         3203 ns          100
RBTreeBenchmark/RBTreeTopDownDelete/4096_stddev               58.6 ns         58.1 ns          100
RBTreeBenchmark/RBTreeTopDownDelete/4096_cv                   1.81 %          1.81 %           100
RBTreeBenchmark/RBTreeTopDownDelete/16384_mean                3341 ns         3316 ns          100
RBTreeBenchmark/RBTreeTopDownDelete/16384_median              3338 ns         3314 ns          100
RBTreeBenchmark/RBTreeTopDownDelete/16384_stddev              67.3 ns         67.8 ns          100
RBTreeBenchmark/RBTreeTopDownDelete/16384_cv                  2.01 %          2.04 %           100
RBTreeBenchmark/RBTreeTopDownDelete/65536_mean                3966 ns         3950 ns          100
RBTreeBenchmark/RBTreeTopDownDelete/65536_median              3944 ns         3931 ns          100
RBTreeBenchmark/RBTreeTopDownDelete/65536_stddev               103 ns          103 ns          100
RBTreeBenchmark/RBTreeTopDownDelete/65536_cv                  2.58 %          2.61 %           100
RBTreeBenchmark/RBTreeTopDownDelete/262144_mean              10233 ns        10261 ns          100
RBTreeBenchmark/RBTreeTopDownDelete/262144_median            10251 ns        10280 ns          100
RBTreeBenchmark/RBTreeTopDownDelete/262144_stddev              216 ns          215 ns          100
RBTreeBenchmark/RBTreeTopDownDelete/262144_cv                 2.11 %          2.09 %           100
RBTreeBenchmark/RBTreeTopDownDelete/1048576_mean             18254 ns        18293 ns          100
RBTreeBenchmark/RBTreeTopDownDelete/1048576_median           18266 ns        18307 ns          100
RBTreeBenchmark/RBTreeTopDownDelete/1048576_stddev             498 ns          502 ns          100
RBTreeBenchmark/RBTreeTopDownDelete/1048576_cv                2.73 %          2.74 %           100
RBTreeBenchmark/RBTreeTopDownDelete/4194304_mean             25242 ns        25283 ns          100
RBTreeBenchmark/RBTreeTopDownDelete/4194304_median           25224 ns        25271 ns          100
RBTreeBenchmark/RBTreeTopDownDelete/4194304_stddev             727 ns          728 ns          100
RBTreeBenchmark/RBTreeTopDownDelete/4194304_cv                2.88 %          2.88 %           100
RBTreeBenchmark/RBTreeSTLDelete/1024_mean                     3167 ns         3138 ns          100
RBTreeBenchmark/RBTreeSTLDelete/1024_median                   3172 ns         3145 ns          100
RBTreeBenchmark/RBTreeSTLDelete/1024_stddev                   61.1 ns         60.6 ns          100
RBTreeBenchmark/RBTreeSTLDelete/1024_cv                       1.93 %          1.93 %           100
RBTreeBenchmark/RBTreeSTLDelete/4096_mean                     3160 ns         3133 ns          100
RBTreeBenchmark/RBTreeSTLDelete/4096_median                   3156 ns         3129 ns          100
RBTreeBenchmark/RBTreeSTLDelete/4096_stddev                   64.9 ns         65.6 ns          100
RBTreeBenchmark/RBTreeSTLDelete/4096_cv                       2.05 %          2.10 %           100
RBTreeBenchmark/RBTreeSTLDelete/16384_mean                    3352 ns         3324 ns          100
RBTreeBenchmark/RBTreeSTLDelete/16384_median                  3258 ns         3234 ns          100
RBTreeBenchmark/RBTreeSTLDelete/16384_stddev                   320 ns          320 ns          100
RBTreeBenchmark/RBTreeSTLDelete/16384_cv                      9.56 %          9.62 %           100
RBTreeBenchmark/RBTreeSTLDelete/65536_mean                    3453 ns         3430 ns          100
RBTreeBenchmark/RBTreeSTLDelete/65536_median                  3449 ns         3426 ns          100
RBTreeBenchmark/RBTreeSTLDelete/65536_stddev                  64.3 ns         65.2 ns          100
RBTreeBenchmark/RBTreeSTLDelete/65536_cv                      1.86 %          1.90 %           100
RBTreeBenchmark/RBTreeSTLDelete/262144_mean                   6673 ns         6674 ns          100
RBTreeBenchmark/RBTreeSTLDelete/262144_median                 6669 ns         6670 ns          100
RBTreeBenchmark/RBTreeSTLDelete/262144_stddev                  122 ns          124 ns          100
RBTreeBenchmark/RBTreeSTLDelete/262144_cv                     1.82 %          1.86 %           100
RBTreeBenchmark/RBTreeSTLDelete/1048576_mean                 14985 ns        15004 ns          100
RBTreeBenchmark/RBTreeSTLDelete/1048576_median               14976 ns        14993 ns          100
RBTreeBenchmark/RBTreeSTLDelete/1048576_stddev                 382 ns          383 ns          100
RBTreeBenchmark/RBTreeSTLDelete/1048576_cv                    2.55 %          2.55 %           100
RBTreeBenchmark/RBTreeSTLDelete/4194304_mean                 22391 ns        22411 ns          100
RBTreeBenchmark/RBTreeSTLDelete/4194304_median               22405 ns        22424 ns          100
RBTreeBenchmark/RBTreeSTLDelete/4194304_stddev                 868 ns          869 ns          100
RBTreeBenchmark/RBTreeSTLDelete/4194304_cv                    3.88 %          3.88 %           100
</pre>
