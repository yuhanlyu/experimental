Benchmark of following algorithms for rotating an array.
1. Rotating an array by using reverse (RotateReverse).
1. An algorithm (JugglingBentley) from Jon Bentley's Programming Pearls that is 
   based on permutation cycle.
1. Another algorithm (JugglingShene) based on permutation cycle from the 
   following paper:  
   Ching-Kuang Shene, An Analysis of Two In-Place Array Rotation Algorithms  
   The Computer Journal (1997) 40 (9): 541-546.  
1. An algorithm (BlockSwapShene) based on swapping sections from the following
   paper:  
   Ching-Kuang Shene,
   An Analysis of Two In-Place Array Rotation Algorithms
   The Computer Journal (1997) 40 (9): 541-546.
1. Another algorithm (BlockSwapGries) based on swapping sections from the
   following paper:  
   David Gries and Harlan Mills,
   Swapping sections.
   Technical Report TR 81-452, Cornell University.

Algorithm that is designed based on swapping sections tends to move elements
fewer times.

Gries-Mills's method is faster than other methods, which confirms the result on
[Dr.Dobb's](http://www.drdobbs.com/parallel/benchmarking-block-swapping-algorithms/232900395).

However, Gries-Mill's method is slower when rotate for a very small or large
amount, but is faster when rotate a moderately large amount.

<pre>
------------------------------------------------------------------------
Benchmark                                 Time           CPU Iterations
------------------------------------------------------------------------
Rotation/JugglingBentley/1          1930671 ns    1930762 ns        360
Rotation/JugglingBentley/6561       1948709 ns    1948807 ns        355
Rotation/JugglingBentley/1048575    1937331 ns    1937442 ns        359
Rotation/JugglingShene/1            2054296 ns    2054413 ns        339
Rotation/JugglingShene/6561         2060655 ns    2060777 ns        329
Rotation/JugglingShene/1048575      2058183 ns    2058311 ns        336
Rotation/RotateReverse/1             634941 ns     634977 ns       1072
Rotation/RotateReverse/6561          635921 ns     635953 ns       1055
Rotation/RotateReverse/1048575       635364 ns     635401 ns       1075
Rotation/BlockSwapShene/1           1196418 ns    1196489 ns        585
Rotation/BlockSwapShene/6561         971018 ns     971056 ns        713
Rotation/BlockSwapShene/1048575      970796 ns     970801 ns        703
Rotation/BlockSwapGries/1           3326233 ns    3326317 ns        210
Rotation/BlockSwapGries/6561         180941 ns     180952 ns       3804
Rotation/BlockSwapGries/1048575     2493580 ns    2493716 ns        281
</pre>
