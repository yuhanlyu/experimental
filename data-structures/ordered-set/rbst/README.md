## Randomized binary search tree
[Randomized binary search tree](https://en.wikipedia.org/wiki/Treap#Randomized_binary_search_tree)
is a randomized self-balancing binary search tree. The operations of insertion
and deletion can be done in O(lg n) time in expectation.

## Benchmark
The randomized binary search tree seems slower than Treap due to excessively
generating random numbers.
<pre>
------------------------------------------------------------------------
Benchmark                                 Time           CPU Iterations
------------------------------------------------------------------------
RBSTBenchmark/RBSTInsert/1024        174246 ns     172878 ns       4075
RBSTBenchmark/RBSTInsert/4096        786270 ns     780399 ns        890
RBSTBenchmark/RBSTInsert/16384      4097387 ns    4063277 ns        172
RBSTBenchmark/RBSTInsert/65536     21184639 ns   21186163 ns         33
RBSTBenchmark/RBSTInsert/262144   147804470 ns  147810047 ns          6
RBSTBenchmark/RBSTInsert/1048576  851958056 ns  851991902 ns          1
RBSTBenchmark/RBSTDelete/1024        136405 ns     135906 ns       5056
RBSTBenchmark/RBSTDelete/4096        723154 ns     720074 ns        968
RBSTBenchmark/RBSTDelete/16384      4119151 ns    4072453 ns        171
RBSTBenchmark/RBSTDelete/65536     28129261 ns   27950866 ns         26
RBSTBenchmark/RBSTDelete/262144   183824963 ns  181757946 ns          4
RBSTBenchmark/RBSTDelete/1048576 1000288405 ns 1000332559 ns          1
</pre>
