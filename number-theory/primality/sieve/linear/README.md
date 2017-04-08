# Linear sieve

Sieve of Eratosthenes takes O(n lg lg n) time to find all primes up to n.
Linear sieve can find all primes up to n in O(n) time.

This module contains Paul Pritchard's linear sieve:  
[Linear prime-number sieves: A family tree](https://doi.org/10.1016/0167-6423(87)90024-4)
Science of Computer Programming  
Volume 9, Issue 1, August 1987, Pages 17-35  

## Benchmark
Since the Google benchmark cannot take int64 as input range, the unit of input
size of bitset version is 1024.

Linear sieve is slower than improved sieve of Eratosthenes.

<pre>
--------------------------------------------------------------------------
Benchmark                                  Time             CPU Iterations
--------------------------------------------------------------------------
BM_LinearSieve/1024                     1280 ns         1280 ns   10920630
BM_LinearSieve/2048                     2659 ns         2659 ns    5263756
BM_LinearSieve/4096                     5315 ns         5315 ns    2632858
BM_LinearSieve/8192                    10809 ns        10809 ns    1291763
BM_LinearSieve/16384                   22034 ns        22034 ns     634778
BM_LinearSieve/32768                   45887 ns        45887 ns     304472
BM_LinearSieve/65536                  101690 ns       101689 ns     138020
BM_LinearSieve/131072                 216103 ns       216100 ns      64812
BM_LinearSieve/262144                 437686 ns       437680 ns      31934
BM_LinearSieve/524288                 876461 ns       876446 ns      15968
BM_LinearSieve/1048576               1738929 ns      1738903 ns       8052
BM_LinearSieve/2097152               3460441 ns      3460380 ns       4048
BM_LinearSieve/4194304               6902038 ns      6901917 ns       2026
BM_LinearSieve/8388608              13825933 ns     13825693 ns       1013
BM_LinearSieve/16777216             27749716 ns     27749108 ns        505
BM_LinearSieve/33554432             58830611 ns     58830123 ns        237
BM_LinearSieve/67108864            128474101 ns    128472918 ns        109
BM_LinearSieve/134217728           273103752 ns    273096203 ns         50
BM_LinearSieve/268435456           551772600 ns    551767929 ns         25
BM_LinearSieve/536870912          1115206698 ns   1115195784 ns         12
BM_LinearSieve/1073741824         2252006303 ns   2251979769 ns          6
BM_ImprovedSieve/1024                    411 ns          410 ns   34078862
BM_ImprovedSieve/2048                    835 ns          835 ns   16784353
BM_ImprovedSieve/4096                   1773 ns         1773 ns    7894106
BM_ImprovedSieve/8192                   3811 ns         3811 ns    3739351
BM_ImprovedSieve/16384                  7691 ns         7691 ns    1813801
BM_ImprovedSieve/32768                 16498 ns        16498 ns     844054
BM_ImprovedSieve/65536                 40924 ns        40924 ns     342567
BM_ImprovedSieve/131072               100129 ns       100128 ns     100000
BM_ImprovedSieve/262144               231333 ns       231331 ns      60535
BM_ImprovedSieve/524288               503289 ns       503283 ns      27877
BM_ImprovedSieve/1048576             1086053 ns      1086039 ns      12903
BM_ImprovedSieve/2097152             2311209 ns      2311182 ns       6064
BM_ImprovedSieve/4194304             4938349 ns      4938295 ns       2834
BM_ImprovedSieve/8388608            10473630 ns     10473510 ns       1334
BM_ImprovedSieve/16777216           22103592 ns     22103276 ns        634
BM_ImprovedSieve/33554432           49283793 ns     49283133 ns        296
BM_ImprovedSieve/67108864           98259961 ns     98258707 ns        143
BM_ImprovedSieve/134217728         203428536 ns    203426011 ns         69
BM_ImprovedSieve/268435456         417655208 ns    417650567 ns         34
BM_ImprovedSieve/536870912         853932033 ns    853921966 ns         16
BM_ImprovedSieve/1073741824       1741474780 ns   1741455403 ns          8
BM_LinearSieveBitset/1                  3751 ns         3730 ns    3752026
BM_LinearSieveBitset/2                  7683 ns         7659 ns    1827364
BM_LinearSieveBitset/4                 15655 ns        15712 ns     891333
BM_LinearSieveBitset/8                 32050 ns        32089 ns     436403
BM_LinearSieveBitset/16                65400 ns        65370 ns     213976
BM_LinearSieveBitset/32               133963 ns       133968 ns     104471
BM_LinearSieveBitset/64               277331 ns       277395 ns      50483
BM_LinearSieveBitset/128              569842 ns       569246 ns      24584
BM_LinearSieveBitset/256             1152868 ns      1150353 ns      12168
BM_LinearSieveBitset/512             2310787 ns      2308749 ns       6065
BM_LinearSieveBitset/1024            4623175 ns      4621350 ns       3029
BM_LinearSieveBitset/2048            9262891 ns      9267682 ns       1511
BM_LinearSieveBitset/4096           18784771 ns     18789868 ns        752
BM_LinearSieveBitset/8192           37378477 ns     37382514 ns        374
BM_LinearSieveBitset/16384          75404076 ns     75404314 ns        184
BM_LinearSieveBitset/32768         150973183 ns    150967650 ns         93
BM_LinearSieveBitset/65536         303317744 ns    303298747 ns         46
BM_LinearSieveBitset/131072        622283300 ns    622233962 ns         22
BM_LinearSieveBitset/262144       1423445657 ns   1424090804 ns         10
BM_LinearSieveBitset/524288       2945352274 ns   2946420294 ns          5
BM_LinearSieveBitset/1048576      6008269684 ns   6009834845 ns          2
BM_LinearSieveBitset/2097152     12193915943 ns  12196466916 ns          1
BM_LinearSieveBitset/4194304     24642772885 ns  24646479795 ns          1
BM_LinearSieveBitset/8388608     49733214224 ns  49736833116 ns          1
BM_LinearSieveBitset/16777216   100991302514 ns 100991816089 ns          1
BM_ImprovedSieveBitset/1                 756 ns          756 ns   18534934
BM_ImprovedSieveBitset/2                1534 ns         1534 ns    9130662
BM_ImprovedSieveBitset/4                3205 ns         3205 ns    4370439
BM_ImprovedSieveBitset/8                6598 ns         6597 ns    2122873
BM_ImprovedSieveBitset/16              13598 ns        13595 ns    1030129
BM_ImprovedSieveBitset/32              28652 ns        28647 ns     487315
BM_ImprovedSieveBitset/64              64782 ns        64771 ns     217648
BM_ImprovedSieveBitset/128            148784 ns       148760 ns      91987
BM_ImprovedSieveBitset/256            325310 ns       325262 ns      43039
BM_ImprovedSieveBitset/512            692475 ns       692383 ns      20248
BM_ImprovedSieveBitset/1024          1457249 ns      1457065 ns       9609
BM_ImprovedSieveBitset/2048          3070995 ns      3070639 ns       4558
BM_ImprovedSieveBitset/4096          6473797 ns      6473096 ns       2164
BM_ImprovedSieveBitset/8192         13635850 ns     13634460 ns       1028
BM_ImprovedSieveBitset/16384        28421569 ns     28418827 ns        493
BM_ImprovedSieveBitset/32768        58861502 ns     58856181 ns        238
BM_ImprovedSieveBitset/65536       121420731 ns    121409963 ns        115
BM_ImprovedSieveBitset/131072      261715764 ns    261693484 ns         54
BM_ImprovedSieveBitset/262144      710182405 ns    710123053 ns         20
BM_ImprovedSieveBitset/524288     1528706710 ns   1528587537 ns          9
BM_ImprovedSieveBitset/1048576    3189576401 ns   3189331013 ns          4
BM_ImprovedSieveBitset/2097152    6603644786 ns   6603157035 ns          2
BM_ImprovedSieveBitset/4194304   13587062697 ns  13586069827 ns          1
BM_ImprovedSieveBitset/8388608   27910053563 ns  27908055983 ns          1
BM_ImprovedSieveBitset/16777216  57483404191 ns  57479420369 ns          1
</pre>
