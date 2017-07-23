## Skip list
[Skip list](https://en.wikipedia.org/wiki/Skip_list) is a randomized dictionary.
The operations of insertion and deletion can be done in O(lg n) time in
expectation.

I used [flexible array member](https://en.wikipedia.org/wiki/Flexible_array_member)
to implement the nodes in skip list, although flexible array member is only
supported in C99 but not in C++. Moreover, each insertion can only increase the
level by at most one, which differs from the original paper.

## Benchmark
<pre>
--------------------------------------------------------------------------------
Benchmark                                         Time           CPU Iterations
--------------------------------------------------------------------------------
SkipListBenchmark/SkipListInsert/1024        115854 ns     115858 ns       6037
SkipListBenchmark/SkipListInsert/4096        544438 ns     544430 ns       1297
SkipListBenchmark/SkipListInsert/16384      3035884 ns    3035827 ns        228
SkipListBenchmark/SkipListInsert/65536     16602523 ns   16589977 ns         42
SkipListBenchmark/SkipListInsert/262144   114494898 ns  114491172 ns          7
SkipListBenchmark/SkipListInsert/1048576  825629709 ns  825599842 ns          1
SkipListBenchmark/SkipListDelete/1024         96321 ns      96328 ns       7330
SkipListBenchmark/SkipListDelete/4096        567574 ns     567596 ns       1230
SkipListBenchmark/SkipListDelete/16384      3340629 ns    3340498 ns        210
SkipListBenchmark/SkipListDelete/65536     21726164 ns   21725244 ns         32
SkipListBenchmark/SkipListDelete/262144   133153342 ns  133146452 ns          5
SkipListBenchmark/SkipListDelete/1048576  793384594 ns  793319928 ns          1
</pre>
