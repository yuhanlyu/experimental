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
WAVLBenchmark/WAVLRecursiveInsert/1024         87214 ns      87231 ns       7818
WAVLBenchmark/WAVLRecursiveInsert/4096        413230 ns     413254 ns       1688
WAVLBenchmark/WAVLRecursiveInsert/16384      2417971 ns    2418071 ns        290
WAVLBenchmark/WAVLRecursiveInsert/65536     13164263 ns   13162821 ns         53
WAVLBenchmark/WAVLRecursiveInsert/262144    78778237 ns   78778467 ns         10
WAVLBenchmark/WAVLRecursiveInsert/1048576  568883262 ns  568892504 ns          1

---------------------------------------------------------------------------------
Benchmark                                          Time           CPU Iterations
---------------------------------------------------------------------------------
WAVLBenchmark/WAVLRecursiveDelete/1024         80201 ns      80183 ns       8571
WAVLBenchmark/WAVLRecursiveDelete/4096        376440 ns     376415 ns       1845
WAVLBenchmark/WAVLRecursiveDelete/16384      2187644 ns    2187648 ns        317
WAVLBenchmark/WAVLRecursiveDelete/65536     11956023 ns   11956147 ns         58
WAVLBenchmark/WAVLRecursiveDelete/262144    73249359 ns   73250620 ns         10
WAVLBenchmark/WAVLRecursiveDelete/1048576  576923618 ns  576936327 ns          1
</pre>
