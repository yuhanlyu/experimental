Summing an array of floating point numbers.
I tested four methods: naive, loop-unroll, std::accumulate, and
std::valarray.sum. Among them, loop-unroll is the fastest one.

SumBenchmark/ForLoop/16777216      18423566 ns   18423121 ns         38
SumBenchmark/UnrollLoop/16777216    9356861 ns    9357043 ns         73
SumBenchmark/Accumulate/16777216   18388261 ns   18388698 ns         38
SumBenchmark/Valarray/16777216     18419235 ns   18419603 ns         38
