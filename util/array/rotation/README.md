# Rotate an array
I compared the following algorithms for rotating an array.
1. Rotating an array by using reverse (RotateReverse).
1. An algorithm (JugglingBentley) from Jon Bentley's Programming Pearls that is 
   based on permutation cycle.
1. Another algorithm (JugglingShene) based on permutation cycle from the 
   following paper:  
   Ching-Kuang Shene,  
   [An Analysis of Two In-Place Array Rotation Algorithms](https://doi.org/10.1093/comjnl/40.9.541)  
   The Computer Journal (1997) 40 (9): 541-546.  
1. An algorithm (BlockSwapShene) based on swapping sections from the following
   paper:  
   Ching-Kuang Shene,
   [An Analysis of Two In-Place Array Rotation Algorithms](https://doi.org/10.1093/comjnl/40.9.541)  
   The Computer Journal (1997) 40 (9): 541-546.
1. Another algorithm (BlockSwapGries) based on swapping sections from the
   following paper:  
   David Gries and Harlan Mills,
   [Swapping sections](http://hdl.handle.net/1813/6292)  
   Technical Report TR 81-452, Cornell University.

Algorithm that is designed based on swapping sections tends to move elements
fewer times.

Gries-Mills's method is faster than other methods, which confirms the result on
[Dr.Dobb's](http://www.drdobbs.com/parallel/benchmarking-block-swapping-algorithms/232900395).

However, Gries-Mill's method is slower when rotate for a very small or large
amount, but is faster when rotate a moderately large amount.

## Benchmark

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

## Perf
When rotate the array by 6561 positions,
<pre>
JugglingBentley
     3,441,076,741      cycles                                                        (38.67%)
     6,509,268,385      instructions              #    1.89  insn per cycle           (46.57%)
       436,166,696      branches                                                      (46.79%)
            58,482      branch-misses             #    0.01% of all branches          (46.95%)
       435,271,481      L1-dcache-load-misses     #   99.47% of all L1-dcache hits    (46.95%)
       437,604,821      L1-dcache-loads                                               (46.95%)
       443,105,152      L1-dcache-stores                                              (30.61%)
         2,462,239      LLC-load-misses           #    0.53% of all LL-cache hits     (30.40%)
       461,085,786      LLC-loads                                                     (31.33%)
             1,180      LLC-store-misses                                              (15.60%)
           285,943      LLC-stores                                                    (15.53%)
             3,914      branch-load-misses                                            (23.20%)
       439,529,253      branch-loads                                                  (30.80%)
JugglingShene
     3,454,824,610      cycles                                                        (38.66%)
     7,700,881,571      instructions              #    2.23  insn per cycle           (46.55%)
       457,600,573      branches                                                      (46.78%)
            50,940      branch-misses             #    0.01% of all branches          (47.00%)
       460,574,832      L1-dcache-load-misses     #   99.23% of all L1-dcache hits    (47.22%)
       464,168,259      L1-dcache-loads                                               (47.44%)
       464,075,997      L1-dcache-stores                                              (31.36%)
           505,207      LLC-load-misses           #    0.10% of all LL-cache hits     (30.95%)
       485,323,973      LLC-loads                                                     (30.53%)
               320      LLC-store-misses                                              (15.02%)
             4,113      LLC-stores                                                    (15.54%)
             2,034      branch-load-misses                                            (23.20%)
       449,948,257      branch-loads                                                  (30.80%)
RotateReverse
     2,531,060,791      cycles                                                        (38.58%)
     8,726,008,790      instructions              #    3.45  insn per cycle           (46.50%)
     1,093,711,391      branches                                                      (46.78%)
            55,820      branch-misses             #    0.01% of all branches          (47.09%)
       139,153,345      L1-dcache-load-misses     #    6.34% of all L1-dcache hits    (47.39%)
     2,193,336,447      L1-dcache-loads                                               (47.56%)
     2,214,307,733      L1-dcache-stores                                              (31.65%)
            75,105      LLC-load-misses           #    0.39% of all LL-cache hits     (31.07%)
        19,261,519      LLC-loads                                                     (30.51%)
                40      LLC-store-misses                                              (14.88%)
           293,978      LLC-stores                                                    (15.51%)
             5,842      branch-load-misses                                            (23.11%)
     1,095,817,769      branch-loads                                                  (30.63%)
BlockSwapShene
     2,956,327,326      cycles                                                        (38.75%)
     9,420,129,957      instructions              #    3.19  insn per cycle           (46.68%)
       730,763,068      branches                                                      (46.94%)
           168,194      branch-misses             #    0.02% of all branches          (47.21%)
        93,105,735      L1-dcache-load-misses     #    6.28% of all L1-dcache hits    (47.47%)
     1,482,686,529      L1-dcache-loads                                               (47.74%)
     1,511,380,224      L1-dcache-stores                                              (31.70%)
            22,868      LLC-load-misses           #   33.20% of all LL-cache hits     (31.24%)
            68,875      LLC-loads                                                     (30.75%)
               316      LLC-store-misses                                              (14.86%)
             2,701      LLC-stores                                                    (15.55%)
           118,007      branch-load-misses                                            (23.21%)
       727,150,314      branch-loads                                                  (30.78%)
BlockSwapGries
     3,284,188,900      cycles                                                        (38.71%)
     6,379,127,190      instructions              #    1.94  insn per cycle           (46.61%)
       641,475,157      branches                                                      (46.85%)
           842,670      branch-misses             #    0.13% of all branches          (47.09%)
       622,226,647      L1-dcache-load-misses     #   24.84% of all L1-dcache hits    (47.32%)
     2,504,646,318      L1-dcache-loads                                               (47.55%)
     1,914,453,086      L1-dcache-stores                                              (31.59%)
           323,003      LLC-load-misses           #    0.70% of all LL-cache hits     (31.45%)
        46,310,498      LLC-loads                                                     (31.12%)
             2,503      LLC-store-misses                                              (14.98%)
             3,312      LLC-stores                                                    (14.85%)
           793,849      branch-load-misses                                            (23.19%)
       641,757,956      branch-loads                                                  (30.78%)
</pre>

From the result, we can see that BlockSwapGries has lower L1 chche-miss rate,
while using fewer instructions.
