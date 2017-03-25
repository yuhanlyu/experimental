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
Rotation/JugglingBentley/1          1926011 ns    1926314 ns        360
Rotation/JugglingBentley/6561       1952001 ns    1952302 ns        357
Rotation/JugglingBentley/1048575    1935084 ns    1935388 ns        360
Rotation/JugglingShene/1            2053358 ns    2053660 ns        339
Rotation/JugglingShene/6561         2076860 ns    2077137 ns        325
Rotation/JugglingShene/1048575      2059388 ns    2059680 ns        338
Rotation/RotateReverse/1             637251 ns     637343 ns       1071
Rotation/RotateReverse/6561          636345 ns     636441 ns       1073
Rotation/RotateReverse/1048575       637372 ns     637470 ns       1072
Rotation/BlockSwapShene/1           1193384 ns    1193559 ns        578
Rotation/BlockSwapShene/6561         972431 ns     972569 ns        713
Rotation/BlockSwapShene/1048575      971878 ns     972021 ns        714
Rotation/BlockSwapGries/1           3331333 ns    3331805 ns        211
Rotation/BlockSwapGries/6561         180913 ns     180940 ns       3803
Rotation/BlockSwapGries/1048575     2491959 ns    2492326 ns        281
</pre>
