## Binary search tree
[Scapegoat tree](https://en.wikipedia.org/wiki/Scapegoat_tree) is a
self-balancing binary search tree without storing any additional information
in each tree node. In this module, the rebalance is done by copy all elements
to an array and rebuild the tree. Thus, the rebalance requires O(n) additional
memory.

## Benchmark
<pre>
--------------------------------------------------------------------------------------------
Benchmark                                                     Time           CPU Iterations
--------------------------------------------------------------------------------------------
ScapegoatBenchmark/ScapegoatTreeInsert/1024              238407 ns     238422 ns       2967
ScapegoatBenchmark/ScapegoatTreeInsert/4096              985186 ns     985179 ns        670
ScapegoatBenchmark/ScapegoatTreeInsert/16384            4837468 ns    4837385 ns        145
ScapegoatBenchmark/ScapegoatTreeInsert/65536           23697194 ns   23696501 ns         29
ScapegoatBenchmark/ScapegoatTreeInsert/262144         131309239 ns  131305851 ns          6
ScapegoatBenchmark/ScapegoatTreeInsert/1048576        752963802 ns  752907476 ns          1
ScapegoatRemoveBenchmark/ScapegoatTreeRemove/1024         79323 ns      79320 ns       8850
ScapegoatRemoveBenchmark/ScapegoatTreeRemove/4096        367183 ns     367136 ns       1907
ScapegoatRemoveBenchmark/ScapegoatTreeRemove/16384      2210633 ns    2210515 ns        317
ScapegoatRemoveBenchmark/ScapegoatTreeRemove/65536     12070100 ns   12069734 ns         56
ScapegoatRemoveBenchmark/ScapegoatTreeRemove/262144    81056429 ns   81054228 ns          9
ScapegoatRemoveBenchmark/ScapegoatTreeRemove/1048576  760496967 ns  760478449 ns          1
</pre>
