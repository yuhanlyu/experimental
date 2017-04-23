## Rebalance of binary search tree
This module contains four linear-time methods of rebalancing a binary search tree.
1. Naive: copy the nodes to an array and then rebuild.
1. Flatten the tree and recursively rebuild: this routine is used in [Scapegoat tree](https://en.wikipedia.org/wiki/Scapegoat_tree) from the following paper:  
Igal Galperin  
[On consulting a set of experts and searching](http://hdl.handle.net/1721.1/10639)  
This thesis also contains an iterative version, but I didn't implement that version.
1. Day's method: the method from the following paper:  
Colin A. Day  
[Balancing a Binary Tree](https://doi.org/10.1093/comjnl/19.4.360)
1. [Day–Stout–Warren algorithm](https://en.wikipedia.org/wiki/Day%E2%80%93Stout%E2%80%93Warren_algorithm):
this is an improvement of the Day's method proposed in the following paper:  
Quentin F. Stout, Bette L. Warren  
[Tree rebalancing in optimal time and space](https://dx.doi.org/10.1145%2F6592.6599)

The Naive method uses linear space. The Galperin and Day's methods use space linear
in the tree height. Day–Stout–Warren algorithm uses only constant number of
variables.

Timothy J. Rolfe wrote a good summary of this topic:  
Timothy J. Rolfe  
[One-time binary search tree balancing: the Day/Stout/Warren (DSW) algorithm](https://dx.doi.org/10.1145%2F820127.820173)

## Benchmark
When the number of nodes grows, the naive method is faster than other methods.

<pre>
----------------------------------------------------------------------------------------
Benchmark                                                 Time           CPU Iterations
----------------------------------------------------------------------------------------
BSTRebalanceBenchmark/NaiveRebalance/1024             21499 ns      21495 ns      33069
BSTRebalanceBenchmark/NaiveRebalance/4096             94263 ns      94260 ns       7420
BSTRebalanceBenchmark/NaiveRebalance/16384           538416 ns     538387 ns       1298
BSTRebalanceBenchmark/NaiveRebalance/65536          2628169 ns    2628050 ns        264
BSTRebalanceBenchmark/NaiveRebalance/262144        19364785 ns   19364242 ns         36
BSTRebalanceBenchmark/NaiveRebalance/1048576      146965461 ns  146957737 ns          5
BSTRebalanceBenchmark/RebalanceByFlatten/1024         18266 ns      18260 ns      38346
BSTRebalanceBenchmark/RebalanceByFlatten/4096         82275 ns      82266 ns       8482
BSTRebalanceBenchmark/RebalanceByFlatten/16384       494368 ns     494328 ns       1406
BSTRebalanceBenchmark/RebalanceByFlatten/65536      2423897 ns    2423816 ns        286
BSTRebalanceBenchmark/RebalanceByFlatten/262144    20671357 ns   20670870 ns         34
BSTRebalanceBenchmark/RebalanceByFlatten/1048576  207783302 ns  207775657 ns          3
BSTRebalanceBenchmark/RebalanceDay/1024               19217 ns      19210 ns      36117
BSTRebalanceBenchmark/RebalanceDay/4096               96399 ns      96394 ns       7267
BSTRebalanceBenchmark/RebalanceDay/16384             622057 ns     622013 ns       1102
BSTRebalanceBenchmark/RebalanceDay/65536            3164909 ns    3164750 ns        219
BSTRebalanceBenchmark/RebalanceDay/262144          25714706 ns   25713882 ns         27
BSTRebalanceBenchmark/RebalanceDay/1048576        271606988 ns  271595847 ns          3
BSTRebalanceBenchmark/RebalanceDSW/1024               19881 ns      19883 ns      35242
BSTRebalanceBenchmark/RebalanceDSW/4096               99892 ns      99891 ns       6975
BSTRebalanceBenchmark/RebalanceDSW/16384             653628 ns     653589 ns       1063
BSTRebalanceBenchmark/RebalanceDSW/65536            3306451 ns    3306297 ns        211
BSTRebalanceBenchmark/RebalanceDSW/262144          29082997 ns   29081871 ns         24
BSTRebalanceBenchmark/RebalanceDSW/1048576        275795528 ns  275783477 ns          3
</pre>
