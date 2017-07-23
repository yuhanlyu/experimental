## AA tree
[AA tree](https://en.wikipedia.org/wiki/AA_tree) is self-balancing binary search
tree. The operations of insertion and deletion can be done in O(lg n) time in
worst case.

## Benchmark
<pre>
----------------------------------------------------------------------------
Benchmark                                     Time           CPU Iterations
----------------------------------------------------------------------------
AATreeBenchmark/AATreeInsert/1024         96927 ns      96790 ns       7257
AATreeBenchmark/AATreeInsert/4096        460424 ns     460502 ns       1525
AATreeBenchmark/AATreeInsert/16384      2669953 ns    2670500 ns        263
AATreeBenchmark/AATreeInsert/65536     14799021 ns   14800879 ns         48
AATreeBenchmark/AATreeInsert/262144    92401499 ns   92416537 ns          9
AATreeBenchmark/AATreeInsert/1048576  675905149 ns  676005196 ns          1
AATreeBenchmark/AATreeDelete/1024         72603 ns      72632 ns       9711
AATreeBenchmark/AATreeDelete/4096        430970 ns     431005 ns       1625
AATreeBenchmark/AATreeDelete/16384      2452925 ns    2453229 ns        283
AATreeBenchmark/AATreeDelete/65536     15046931 ns   15049055 ns         47
AATreeBenchmark/AATreeDelete/262144    94841594 ns   94855289 ns          7
AATreeBenchmark/AATreeDelete/1048576  551894631 ns  551937451 ns          1
</pre>
