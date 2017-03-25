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

Rotation/JugglingBentley/1          1935962 ns    1935918 ns        358
Rotation/JugglingBentley/6561       2255485 ns    2255367 ns        308
Rotation/JugglingBentley/1048575    1937420 ns    1937333 ns        357
Rotation/JugglingShene/1            2055267 ns    2055218 ns        339
Rotation/JugglingShene/6561         2089076 ns    2088959 ns        321
Rotation/JugglingShene/1048575      2059829 ns    2059725 ns        339
Rotation/RotateReverse/1             700030 ns     700008 ns        937
Rotation/RotateReverse/6561          704063 ns     704031 ns        971
Rotation/RotateReverse/1048575       703809 ns     703769 ns        972
Rotation/BlockSwapShene/1           1193164 ns    1193128 ns        579
Rotation/BlockSwapShene/6561         975066 ns     973291 ns        711
Rotation/BlockSwapShene/1048575      976381 ns     973077 ns        710
Rotation/BlockSwapGries/1           3331396 ns    3328737 ns        210
Rotation/BlockSwapGries/6561         183361 ns     182895 ns       3815
Rotation/BlockSwapGries/1048575     2501670 ns    2495264 ns        281
