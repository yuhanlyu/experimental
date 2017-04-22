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
------------------------------------------------------------------------------------------
Benchmark                                                   Time           CPU Iterations
------------------------------------------------------------------------------------------
BSTCommonBenchmark/InorderTraverseRec/1024              26276 ns      26273 ns      26691
BSTCommonBenchmark/InorderTraverseRec/4096             111813 ns     111808 ns       6247
BSTCommonBenchmark/InorderTraverseRec/16384            550698 ns     550612 ns       1269
BSTCommonBenchmark/InorderTraverseRec/65536           2447861 ns    2447588 ns        286
BSTCommonBenchmark/InorderTraverseRec/262144         15401359 ns   15400030 ns         44
BSTCommonBenchmark/InorderTraverseRec/1048576       132410383 ns  132400969 ns          5
BSTCommonBenchmark/InorderTraverse/1024                 25942 ns      25944 ns      27066
BSTCommonBenchmark/InorderTraverse/4096                111522 ns     111512 ns       6308
BSTCommonBenchmark/InorderTraverse/16384               554203 ns     554138 ns       1268
BSTCommonBenchmark/InorderTraverse/65536              2455184 ns    2454987 ns        287
BSTCommonBenchmark/InorderTraverse/262144            15389570 ns   15388969 ns         47
BSTCommonBenchmark/InorderTraverse/1048576          133407763 ns  133401469 ns          5
BSTCommonBenchmark/InorderTraverseArray/1024            24635 ns      24645 ns      28498
BSTCommonBenchmark/InorderTraverseArray/4096           105767 ns     105761 ns       6604
BSTCommonBenchmark/InorderTraverseArray/16384          527817 ns     527754 ns       1328
BSTCommonBenchmark/InorderTraverseArray/65536         2358505 ns    2358343 ns        297
BSTCommonBenchmark/InorderTraverseArray/262144       14598427 ns   14597822 ns         49
BSTCommonBenchmark/InorderTraverseArray/1048576     126011816 ns  125985680 ns          6
BSTCommonBenchmark/InorderTraverseMorris/1024           26869 ns      26882 ns      26024
BSTCommonBenchmark/InorderTraverseMorris/4096          116311 ns     116310 ns       6004
BSTCommonBenchmark/InorderTraverseMorris/16384         570189 ns     570013 ns       1233
BSTCommonBenchmark/InorderTraverseMorris/65536        2526887 ns    2526288 ns        277
BSTCommonBenchmark/InorderTraverseMorris/262144      15854939 ns   15854443 ns         44
BSTCommonBenchmark/InorderTraverseMorris/1048576    142251854 ns  142217928 ns          5
BSTCommonBenchmark/PreorderTraverseRec/1024             26209 ns      26202 ns      26691
BSTCommonBenchmark/PreorderTraverseRec/4096            112223 ns     112232 ns       6240
BSTCommonBenchmark/PreorderTraverseRec/16384           551466 ns     551515 ns       1274
BSTCommonBenchmark/PreorderTraverseRec/65536          2438470 ns    2438812 ns        286
BSTCommonBenchmark/PreorderTraverseRec/262144        15040100 ns   15038891 ns         46
BSTCommonBenchmark/PreorderTraverseRec/1048576      128576403 ns  128585307 ns          5
BSTCommonBenchmark/PreorderTraverse/1024                26153 ns      26156 ns      26784
BSTCommonBenchmark/PreorderTraverse/4096               111868 ns     111889 ns       6282
BSTCommonBenchmark/PreorderTraverse/16384              553306 ns     553361 ns       1275
BSTCommonBenchmark/PreorderTraverse/65536             2441114 ns    2441262 ns        286
BSTCommonBenchmark/PreorderTraverse/262144           14955164 ns   14952817 ns         48
BSTCommonBenchmark/PreorderTraverse/1048576         128455735 ns  128440447 ns          5
BSTCommonBenchmark/PreorderTraverseArray/1024           25872 ns      25883 ns      27343
BSTCommonBenchmark/PreorderTraverseArray/4096          110720 ns     110710 ns       6316
BSTCommonBenchmark/PreorderTraverseArray/16384         543785 ns     543795 ns       1289
BSTCommonBenchmark/PreorderTraverseArray/65536        2419898 ns    2419575 ns        290
BSTCommonBenchmark/PreorderTraverseArray/262144      14884047 ns   14884811 ns         48
BSTCommonBenchmark/PreorderTraverseArray/1048576    129639702 ns  129640395 ns          5
BSTCommonBenchmark/PreorderTraverseMorris/1024          26787 ns      26803 ns      26048
BSTCommonBenchmark/PreorderTraverseMorris/4096         114954 ns     114945 ns       6057
BSTCommonBenchmark/PreorderTraverseMorris/16384        568503 ns     568502 ns       1233
BSTCommonBenchmark/PreorderTraverseMorris/65536       2512132 ns    2512010 ns        277
BSTCommonBenchmark/PreorderTraverseMorris/262144     15813144 ns   15813329 ns         43
BSTCommonBenchmark/PreorderTraverseMorris/1048576   140015136 ns  139991612 ns          5
BSTCommonBenchmark/PostorderTraverseRec/1024            28094 ns      28097 ns      24555
BSTCommonBenchmark/PostorderTraverseRec/4096           120408 ns     120414 ns       5802
BSTCommonBenchmark/PostorderTraverseRec/16384          588746 ns     588633 ns       1193
BSTCommonBenchmark/PostorderTraverseRec/65536         2601206 ns    2601231 ns        269
BSTCommonBenchmark/PostorderTraverseRec/262144       15926121 ns   15926116 ns         45
BSTCommonBenchmark/PostorderTraverseRec/1048576     137589448 ns  137587342 ns          5
BSTCommonBenchmark/PostorderTraverse/1024               27800 ns      27804 ns      25109
BSTCommonBenchmark/PostorderTraverse/4096              120547 ns     120542 ns       5820
BSTCommonBenchmark/PostorderTraverse/16384             587734 ns     587716 ns       1187
BSTCommonBenchmark/PostorderTraverse/65536            2604763 ns    2604154 ns        266
BSTCommonBenchmark/PostorderTraverse/262144          16141284 ns   16141141 ns         44
BSTCommonBenchmark/PostorderTraverse/1048576        137374156 ns  137336928 ns          5
BSTCommonBenchmark/PostorderTraverseArray/1024          28085 ns      28079 ns      24975
BSTCommonBenchmark/PostorderTraverseArray/4096         119893 ns     119863 ns       5867
BSTCommonBenchmark/PostorderTraverseArray/16384        586558 ns     586419 ns       1196
BSTCommonBenchmark/PostorderTraverseArray/65536       2607073 ns    2606908 ns        270
BSTCommonBenchmark/PostorderTraverseArray/262144     16196922 ns   16193465 ns         43
BSTCommonBenchmark/PostorderTraverseArray/1048576   136611044 ns  136609513 ns          5
BSTCommonBenchmark/PostorderTraverseMorris/1024         29206 ns      29207 ns      23979
BSTCommonBenchmark/PostorderTraverseMorris/4096        124371 ns     124368 ns       5466
BSTCommonBenchmark/PostorderTraverseMorris/16384       603308 ns     603353 ns       1171
BSTCommonBenchmark/PostorderTraverseMorris/65536      2647217 ns    2647393 ns        264
BSTCommonBenchmark/PostorderTraverseMorris/262144    16763594 ns   16764760 ns         42
BSTCommonBenchmark/PostorderTraverseMorris/1048576  145273693 ns  145284741 ns          5
BSTCommonBenchmark/LevelOrderTraverseQueue/1024         28803 ns      28781 ns      25717
BSTCommonBenchmark/LevelOrderTraverseQueue/4096        113934 ns     113947 ns       6119
BSTCommonBenchmark/LevelOrderTraverseQueue/16384       529721 ns     529720 ns       1330
BSTCommonBenchmark/LevelOrderTraverseQueue/65536      2298832 ns    2298835 ns        307
BSTCommonBenchmark/LevelOrderTraverseQueue/262144    13799910 ns   13800232 ns         52
BSTCommonBenchmark/LevelOrderTraverseQueue/1048576  109452740 ns  109453156 ns          6
BSTCommonBenchmark/LevelOrderTraverse/1024              25784 ns      25792 ns      27425
BSTCommonBenchmark/LevelOrderTraverse/4096             104767 ns     104775 ns       6708
BSTCommonBenchmark/LevelOrderTraverse/16384            489793 ns     489674 ns       1289
BSTCommonBenchmark/LevelOrderTraverse/65536           2136051 ns    2135580 ns        320
BSTCommonBenchmark/LevelOrderTraverse/262144         12982341 ns   12982179 ns         54
BSTCommonBenchmark/LevelOrderTraverse/1048576       104684760 ns  104683800 ns          7
</pre>
