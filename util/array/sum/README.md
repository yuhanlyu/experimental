Summing an array of floating point numbers.
I tested four methods: naive, loop-unroll, std::accumulate, and
std::valarray.sum. Among them, loop-unroll is the fastest one.

<pre>
------------------------------------------------------------------------
Benchmark                                 Time           CPU Iterations
------------------------------------------------------------------------
SumBenchmark/ForLoop/16777216      18373396 ns   18374621 ns         38
SumBenchmark/UnrollLoop/16777216    9347126 ns    9347775 ns         74
SumBenchmark/Accumulate/16777216   18395499 ns   18396919 ns         38
SumBenchmark/Valarray/16777216     18399688 ns   18401192 ns         38
</pre>
