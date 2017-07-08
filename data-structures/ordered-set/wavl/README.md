## Binary search tree
[WAVL tree](https://en.wikipedia.org/wiki/WAVL_tree) is self-balancing binary search
tree. The operations of insertion and deletion can be done in O(lg n) time in
worst case.

In the worst case, insertion and deletion only perform two rotations (one signle
rotation or one double rotation).

## Benchmark
<pre>
---------------------------------------------------------------------------------
Benchmark                                          Time           CPU Iterations
---------------------------------------------------------------------------------
WAVLBenchmark/WAVLInsert/1024                  71858 ns      71900 ns       9704
WAVLBenchmark/WAVLInsert/4096                 336732 ns     336686 ns       2067
WAVLBenchmark/WAVLInsert/16384               1953513 ns    1953253 ns        358
WAVLBenchmark/WAVLInsert/65536              11094533 ns   11092921 ns         63
WAVLBenchmark/WAVLInsert/262144             78656465 ns   78644058 ns         10
WAVLBenchmark/WAVLInsert/1048576           578242760 ns  578156542 ns          1
WAVLBenchmark/WAVLRecursiveInsert/1024         87621 ns      87643 ns       7968
WAVLBenchmark/WAVLRecursiveInsert/4096        415413 ns     415392 ns       1681
WAVLBenchmark/WAVLRecursiveInsert/16384      2317488 ns    2317356 ns        300
WAVLBenchmark/WAVLRecursiveInsert/65536     12740325 ns   12739034 ns         54
WAVLBenchmark/WAVLRecursiveInsert/262144    96178685 ns   96161537 ns          9
WAVLBenchmark/WAVLRecursiveInsert/1048576  612581195 ns  612511495 ns          1
WAVLBenchmark/WAVLRecursiveDelete/1024         80409 ns      80392 ns       8746
WAVLBenchmark/WAVLRecursiveDelete/4096        387082 ns     387030 ns       1806
WAVLBenchmark/WAVLRecursiveDelete/16384      2168941 ns    2168711 ns        321
WAVLBenchmark/WAVLRecursiveDelete/65536     12174128 ns   12173238 ns         59
WAVLBenchmark/WAVLRecursiveDelete/262144    82700690 ns   82695528 ns          9
WAVLBenchmark/WAVLRecursiveDelete/1048576  600224950 ns  600196375 ns          1
</pre>
