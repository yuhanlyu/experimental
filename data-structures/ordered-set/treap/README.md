## Treap
[Treap](https://en.wikipedia.org/wiki/Treap) is a randomized self-balancing
binary search tree. The operations of insertion and deletion can be done in
O(lg n) time in expectation.

There are two implementations in this module. One implementation uses rotations
when doing insert/delete. Another implementation does not use rotations.
1. Insert: insert a value using rotations and recursion.
1. Delete: delete a value using rotations.
1. InsertWithoutRotation: insert a value without rotations. But this method
   cannot detect duplicated insertion.
1. DeleteWithoutRotation: delete a value without rotations.

## Benchmark
Insert/Delete without rotations seems faster than the original method described
in the paper.
<pre>
--------------------------------------------------------------------------
Benchmark                                   Time           CPU Iterations
--------------------------------------------------------------------------
TreapBenchmark/TreapInsert/1024        112439 ns     112476 ns       6168
TreapBenchmark/TreapInsert/4096        558435 ns     558529 ns       1245
TreapBenchmark/TreapInsert/16384      3276674 ns    3277137 ns        213
TreapBenchmark/TreapInsert/65536     18998713 ns   19000740 ns         36
TreapBenchmark/TreapInsert/262144   154481879 ns  154489500 ns          5
TreapBenchmark/TreapInsert/1048576  984687652 ns  984745707 ns          1

--------------------------------------------------------------------------
Benchmark                                   Time           CPU Iterations
--------------------------------------------------------------------------
TreapBenchmark/TreapDelete/1024         56604 ns      56606 ns      12344
TreapBenchmark/TreapDelete/4096        312676 ns     312658 ns       2249
TreapBenchmark/TreapDelete/16384      2117197 ns    2117169 ns        335
TreapBenchmark/TreapDelete/65536     13014243 ns   13014268 ns         54
TreapBenchmark/TreapDelete/262144   110602907 ns  110598449 ns          6
TreapBenchmark/TreapDelete/1048576  841492615 ns  841470680 ns          1

-----------------------------------------------------------------------------------------
Benchmark                                                  Time           CPU Iterations
-----------------------------------------------------------------------------------------
TreapBenchmark/TreapInsertWithoutRotation/1024         74764 ns      74785 ns       9127
TreapBenchmark/TreapInsertWithoutRotation/4096        389576 ns     389650 ns       1798
TreapBenchmark/TreapInsertWithoutRotation/16384      2526109 ns    2525958 ns        279
TreapBenchmark/TreapInsertWithoutRotation/65536     15215452 ns   15216766 ns         48
TreapBenchmark/TreapInsertWithoutRotation/262144   143947876 ns  143937747 ns          6
TreapBenchmark/TreapInsertWithoutRotation/1048576  983096042 ns  983157490 ns          1

-----------------------------------------------------------------------------------------
Benchmark                                                  Time           CPU Iterations
-----------------------------------------------------------------------------------------
TreapBenchmark/TreapDeleteWithoutRotation/1024         47032 ns      47027 ns      14857
TreapBenchmark/TreapDeleteWithoutRotation/4096        271903 ns     271899 ns       2642
TreapBenchmark/TreapDeleteWithoutRotation/16384      1890706 ns    1890680 ns        366
TreapBenchmark/TreapDeleteWithoutRotation/65536     11494211 ns   11495064 ns         62
TreapBenchmark/TreapDeleteWithoutRotation/262144   100064178 ns  100070166 ns          7
TreapBenchmark/TreapDeleteWithoutRotation/1048576  777080994 ns  777131576 ns          1
</pre>
