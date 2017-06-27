## Binary search tree
[Deterministic Skip List](https://en.wikipedia.org/wiki/Skip_list) is a
self-balanced dictionary.
The operations of insertion and deletion can be done in O(lg n) time in
the worst case.

More information can be found in the following dissertation  
Thomas Papadakis  
Skip Lists and Probabilistic Analysis of Algorithms  
## Benchmark
<pre>
----------------------------------------------------------------------
Benchmark                               Time           CPU Iterations
----------------------------------------------------------------------
DSLBenchmark/DSLInsert/1024         89172 ns      89154 ns       7842
DSLBenchmark/DSLInsert/4096        440293 ns     440117 ns       1595
DSLBenchmark/DSLInsert/16384      2841392 ns    2840041 ns        248
DSLBenchmark/DSLInsert/65536     15274499 ns   15267071 ns         46
DSLBenchmark/DSLInsert/262144   134888928 ns  134822808 ns          6
DSLBenchmark/DSLInsert/1048576  899160905 ns  898714753 ns          1
DSLBenchmark/DSLDelete/1024        165115 ns     165045 ns       4300
DSLBenchmark/DSLDelete/4096        962954 ns     962514 ns        712
DSLBenchmark/DSLDelete/16384      5347233 ns    5344803 ns        132
DSLBenchmark/DSLDelete/65536     33972082 ns   33956425 ns         21
DSLBenchmark/DSLDelete/262144   199347620 ns  199258203 ns          3
DSLBenchmark/DSLDelete/1048576 1046171230 ns 1045701682 ns          1
</pre>
