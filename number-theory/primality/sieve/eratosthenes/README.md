# Sieve of Eratosthenes
[Sieve of Eratosthenes](https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes) is
a method of finding prime numbers up to a given limit.

This module contains two implementations of sieve of Eratosthenes.
1. Ordinary sieve of Eratosthenes.
2. An improvement explained in Chapter 13 of 
   [Algorithms Unplugged](http://dx.doi.org/10.1007/978-3-642-15328-0). 
   This variant reduces the number of memory write by introducing one additional
   comparison.

## Benchmark
Since the Google benchmark cannot take int64 as input range, the unit of input
size of bitset version is 1024.

For the result we can see that he improved sieve of Eratosthenes is faster than
ordinary sieve of Eratosthenes when bitset is not used. The bitset version is
slower than the bool array version but is more memory efficient.
<pre>
------------------------------------------------------------------------
Benchmark                                  Time           CPU Iterations
------------------------------------------------------------------------
BM_Sieve/1024                            288 ns        288 ns   49026670
BM_Sieve/2048                            575 ns        575 ns   24256585
BM_Sieve/4096                           1158 ns       1158 ns   12106276
BM_Sieve/8192                           2541 ns       2541 ns    5512365
BM_Sieve/16384                          5057 ns       5057 ns    2731279
BM_Sieve/32768                         10448 ns      10448 ns    1340405
BM_Sieve/65536                         21550 ns      21549 ns     649411
BM_Sieve/131072                        54211 ns      54209 ns     258583
BM_Sieve/262144                       114881 ns     114876 ns     121916
BM_Sieve/524288                       276690 ns     276677 ns      50600
BM_Sieve/1048576                      715473 ns     715435 ns      19570
BM_Sieve/2097152                     1540005 ns    1539914 ns       9098
BM_Sieve/4194304                     3230440 ns    3230240 ns       4337
BM_Sieve/8388608                     6776435 ns    6776004 ns       2065
BM_Sieve/16777216                   16069684 ns   16068616 ns        867
BM_Sieve/33554432                   64443363 ns   64438859 ns        217
BM_Sieve/67108864                  177685405 ns  177672796 ns         81
BM_Sieve/134217728                 400177176 ns  400143329 ns         32
BM_Sieve/268435456                 846420620 ns  846356874 ns         17
BM_Sieve/536870912                1791010225 ns 1791213471 ns          8
BM_Sieve/1073741824               3743129066 ns 3744592200 ns          4
BM_ImprovedSieve/1024                    409 ns        409 ns   34224153
BM_ImprovedSieve/2048                    836 ns        836 ns   16765439
BM_ImprovedSieve/4096                   1775 ns       1776 ns    7886685
BM_ImprovedSieve/8192                   3720 ns       3721 ns    3749720
BM_ImprovedSieve/16384                  7609 ns       7611 ns    1834599
BM_ImprovedSieve/32768                 16268 ns      16270 ns     855640
BM_ImprovedSieve/65536                 40508 ns      40513 ns     345657
BM_ImprovedSieve/131072                99294 ns      99303 ns     140751
BM_ImprovedSieve/262144               230206 ns     230225 ns      60885
BM_ImprovedSieve/524288               501583 ns     501616 ns      27958
BM_ImprovedSieve/1048576             1084775 ns    1084835 ns      12874
BM_ImprovedSieve/2097152             2314459 ns    2314565 ns       6061
BM_ImprovedSieve/4194304             4930187 ns    4930369 ns       2839
BM_ImprovedSieve/8388608            10448104 ns   10448403 ns       1340
BM_ImprovedSieve/16777216           22056612 ns   22057079 ns        633
BM_ImprovedSieve/33554432           46850521 ns   46851232 ns        296
BM_ImprovedSieve/67108864           98266644 ns   98267634 ns        143
BM_ImprovedSieve/134217728         203357744 ns  203358986 ns         69
BM_ImprovedSieve/268435456         417815610 ns  417816764 ns         34
BM_ImprovedSieve/536870912         853868101 ns  853865580 ns         16
BM_ImprovedSieve/1073741824       1738553416 ns 1738546045 ns          8
BM_SieveBitset/1                         441 ns        441 ns   31753027
BM_SieveBitset/2                         922 ns        922 ns   15178999
BM_SieveBitset/4                        1997 ns       1997 ns    7011356
BM_SieveBitset/8                        4135 ns       4135 ns    3386400
BM_SieveBitset/16                       8619 ns       8618 ns    1624321
BM_SieveBitset/32                      17925 ns      17923 ns     781225
BM_SieveBitset/64                      37328 ns      37325 ns     375021
BM_SieveBitset/128                     77921 ns      77914 ns     179966
BM_SieveBitset/256                    161378 ns     161363 ns      86747
BM_SieveBitset/512                    334049 ns     334019 ns      41907
BM_SieveBitset/1024                   693292 ns     693235 ns      20193
BM_SieveBitset/2048                  1437254 ns    1437139 ns       9738
BM_SieveBitset/4096                  2972561 ns    2972332 ns       4710
BM_SieveBitset/8192                  6785946 ns    6785455 ns       2064
BM_SieveBitset/16384                14636265 ns   14635216 ns        957
BM_SieveBitset/32768                30920338 ns   30918216 ns        453
BM_SieveBitset/65536                64864586 ns   64860391 ns        216
BM_SieveBitset/131072              140545762 ns  140536731 ns        100
BM_SieveBitset/262144              515441360 ns  515409804 ns         27
BM_SieveBitset/524288             1241352859 ns 1241279313 ns         11
BM_SieveBitset/1048576            2814857076 ns 2814689091 ns          5
BM_SieveBitset/2097152            6067182246 ns 6066844930 ns          2
BM_SieveBitset/4194304          12907470858 ns 12906716215 ns          1
BM_SieveBitset/8388608          27242108103 ns 27240566109 ns          1
BM_SieveBitset/16777216         57334201785 ns 57331225639 ns          1
BM_ImprovedSieveBitset/1                 755 ns        755 ns   18540633
BM_ImprovedSieveBitset/2                1535 ns       1535 ns    9083316
BM_ImprovedSieveBitset/4                3203 ns       3203 ns    4370424
BM_ImprovedSieveBitset/8                6596 ns       6595 ns    2122978
BM_ImprovedSieveBitset/16              13602 ns      13601 ns    1027593
BM_ImprovedSieveBitset/32              28820 ns      28819 ns     483939
BM_ImprovedSieveBitset/64              64525 ns      64523 ns     217062
BM_ImprovedSieveBitset/128            147488 ns     147482 ns      95029
BM_ImprovedSieveBitset/256            325188 ns     325175 ns      43053
BM_ImprovedSieveBitset/512            690791 ns     690763 ns      20268
BM_ImprovedSieveBitset/1024          1456445 ns    1456388 ns       9616
BM_ImprovedSieveBitset/2048          3068995 ns    3068873 ns       4561
BM_ImprovedSieveBitset/4096          6469731 ns    6469472 ns       2166
BM_ImprovedSieveBitset/8192         13630108 ns   13629562 ns       1026
BM_ImprovedSieveBitset/16384        28476963 ns   28475884 ns        492
BM_ImprovedSieveBitset/32768        58971047 ns   58968725 ns        237
BM_ImprovedSieveBitset/65536       121614540 ns  121609810 ns        115
BM_ImprovedSieveBitset/131072      257596424 ns  257586450 ns         54
BM_ImprovedSieveBitset/262144      707918513 ns  707890565 ns         20
BM_ImprovedSieveBitset/524288     1522450157 ns 1522388103 ns          9
BM_ImprovedSieveBitset/1048576    3184228359 ns 3184111661 ns          4
BM_ImprovedSieveBitset/2097152    6584862002 ns 6584612687 ns          2
BM_ImprovedSieveBitset/4194304  13565347680 ns 13564861315 ns          1
BM_ImprovedSieveBitset/8388608  27870656964 ns 27869646427 ns          1
BM_ImprovedSieveBitset/16777216 57142806305 ns 57140711815 ns          1
</pre>
