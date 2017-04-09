# Segmented sieve

Sieve of Eratosthenes method tends to have high cache miss rate. One way to
improve the cache performance is to partition the prime array into segments
whose length is approximately equal to the L1 data cache and then sieve
segments one by one. More details can be found on
[primesieve.org](http://primesieve.org/segmented_sieve.html).

The segmented sieve comes from the following paper.
Carter Bays and Richard H. Hudson
[The segmented sieve of eratosthenes and primes in arithmetic progressions to 10^12](https://dx.doi.org/10.1007/BF01932283)

## Benchmark

Segmented sieve is faster than sieve of Eratosthenes method.

<pre>
-------------------------------------------------------------------------
Benchmark                                  Time            CPU Iterations
-------------------------------------------------------------------------
BM_SegmentedSieve/1024                   449 ns         449 ns   31157310
BM_SegmentedSieve/2048                   768 ns         768 ns   18233157
BM_SegmentedSieve/4096                  1509 ns        1509 ns    9253594
BM_SegmentedSieve/8192                  2977 ns        2977 ns    4700870
BM_SegmentedSieve/16384                 5661 ns        5661 ns    2469611
BM_SegmentedSieve/32768                11602 ns       11602 ns    1206986
BM_SegmentedSieve/65536                22924 ns       22924 ns     609763
BM_SegmentedSieve/131072               46803 ns       46802 ns     299214
BM_SegmentedSieve/262144               95985 ns       95983 ns     145931
BM_SegmentedSieve/524288              198138 ns      198135 ns      70740
BM_SegmentedSieve/1048576             414259 ns      414270 ns      34124
BM_SegmentedSieve/2097152             873765 ns      873785 ns      16139
BM_SegmentedSieve/4194304            1803720 ns     1803763 ns       7790
BM_SegmentedSieve/8388608            3735180 ns     3735259 ns       3747
BM_SegmentedSieve/16777216           7765361 ns     7765504 ns       1803
BM_SegmentedSieve/33554432          16416217 ns    16416477 ns        858
BM_SegmentedSieve/67108864          34437018 ns    34437578 ns        394
BM_SegmentedSieve/134217728         70940773 ns    70941861 ns        198
BM_SegmentedSieve/268435456        148588979 ns   148591076 ns         95
BM_SegmentedSieve/536870912        312386467 ns   312390638 ns         45
BM_SegmentedSieve/1073741824       662669087 ns   662677992 ns         21
BM_ImprovedSieve/1024                    439 ns         439 ns   31933064
BM_ImprovedSieve/2048                    919 ns         919 ns   15220422
BM_ImprovedSieve/4096                   1985 ns        1985 ns    7067046
BM_ImprovedSieve/8192                   4304 ns        4304 ns    3381997
BM_ImprovedSieve/16384                  8686 ns        8686 ns    1594098
BM_ImprovedSieve/32768                 19138 ns       19138 ns     729259
BM_ImprovedSieve/65536                 48169 ns       48169 ns     291802
BM_ImprovedSieve/131072               121856 ns      121857 ns     115696
BM_ImprovedSieve/262144               272817 ns      272818 ns      51497
BM_ImprovedSieve/524288               577257 ns      577259 ns      24250
BM_ImprovedSieve/1048576             1228311 ns     1228316 ns      11401
BM_ImprovedSieve/2097152             2603557 ns     2603561 ns       5379
BM_ImprovedSieve/4194304             5534131 ns     5534152 ns       2530
BM_ImprovedSieve/8388608            11751196 ns    11751178 ns       1192
BM_ImprovedSieve/16777216           24844932 ns    24844928 ns        564
BM_ImprovedSieve/33554432           52551286 ns    52551056 ns        267
BM_ImprovedSieve/67108864          109618545 ns   109618137 ns        127
BM_ImprovedSieve/134217728         226395637 ns   226395090 ns         62
BM_ImprovedSieve/268435456         464600897 ns   464599715 ns         30
BM_ImprovedSieve/536870912         948955331 ns   948953018 ns         15
BM_ImprovedSieve/1073741824       1932698181 ns  1932694531 ns          7
BM_SegmentedSieveBitset/1                692 ns         692 ns   20217260
BM_SegmentedSieveBitset/2               1252 ns        1252 ns   11172975
BM_SegmentedSieveBitset/4               2452 ns        2452 ns    5709473
BM_SegmentedSieveBitset/8               4828 ns        4828 ns    2900145
BM_SegmentedSieveBitset/16              9671 ns        9671 ns    1447718
BM_SegmentedSieveBitset/32             19913 ns       19913 ns     703893
BM_SegmentedSieveBitset/64             40528 ns       40527 ns     345509
BM_SegmentedSieveBitset/128            83192 ns       83191 ns     168228
BM_SegmentedSieveBitset/256           171337 ns      171336 ns      81656
BM_SegmentedSieveBitset/512           352474 ns      352473 ns      39724
BM_SegmentedSieveBitset/1024          732334 ns      732330 ns      19114
BM_SegmentedSieveBitset/2048         1510744 ns     1510734 ns       9257
BM_SegmentedSieveBitset/4096         3119979 ns     3119958 ns       4484
BM_SegmentedSieveBitset/8192         7456149 ns     7456089 ns       1877
BM_SegmentedSieveBitset/16384       15167681 ns    15167585 ns        923
BM_SegmentedSieveBitset/32768       30973205 ns    30972937 ns        452
BM_SegmentedSieveBitset/65536       63441414 ns    63440888 ns        221
BM_SegmentedSieveBitset/131072     130181919 ns   130180869 ns        108
BM_SegmentedSieveBitset/262144     266553976 ns   266551616 ns         53
BM_SegmentedSieveBitset/524288     545152766 ns   545148385 ns         26
BM_SegmentedSieveBitset/1048576   1113901894 ns  1113890237 ns         13
BM_SegmentedSieveBitset/2097152   2274592129 ns  2274572716 ns          6
BM_SegmentedSieveBitset/4194304   4634879903 ns  4634833381 ns          3
BM_SegmentedSieveBitset/8388608   9439250971 ns  9439161275 ns          2
BM_SegmentedSieveBitset/16777216 19234261649 ns 19234081452 ns          1
BM_ImprovedSieveBitset/1                 759 ns         759 ns   18527854
BM_ImprovedSieveBitset/2                1534 ns        1534 ns    9129633
BM_ImprovedSieveBitset/4                3204 ns        3204 ns    4366187
BM_ImprovedSieveBitset/8                6599 ns        6598 ns    2121457
BM_ImprovedSieveBitset/16              13622 ns       13622 ns    1026507
BM_ImprovedSieveBitset/32              28520 ns       28519 ns     486262
BM_ImprovedSieveBitset/64              64217 ns       64216 ns     218081
BM_ImprovedSieveBitset/128            147560 ns      147558 ns      94890
BM_ImprovedSieveBitset/256            325254 ns      325250 ns      43034
BM_ImprovedSieveBitset/512            691382 ns      691373 ns      20249
BM_ImprovedSieveBitset/1024          1458335 ns     1458317 ns       9606
BM_ImprovedSieveBitset/2048          3076453 ns     3076415 ns       4554
BM_ImprovedSieveBitset/4096          6478219 ns     6478139 ns       2162
BM_ImprovedSieveBitset/8192         13656996 ns    13656817 ns       1027
BM_ImprovedSieveBitset/16384        28485081 ns    28484781 ns        491
BM_ImprovedSieveBitset/32768        58943714 ns    58942929 ns        237
BM_ImprovedSieveBitset/65536       121584699 ns   121583169 ns        115
BM_ImprovedSieveBitset/131072      254987589 ns   254983391 ns         55
BM_ImprovedSieveBitset/262144      705740911 ns   705729370 ns         20
BM_ImprovedSieveBitset/524288     1521943864 ns  1521926014 ns          9
BM_ImprovedSieveBitset/1048576    3184760035 ns  3184712975 ns          4
BM_ImprovedSieveBitset/2097152    6595908223 ns  6595805070 ns          2
BM_ImprovedSieveBitset/4194304   13584652001 ns 13584441464 ns          1
BM_ImprovedSieveBitset/8388608   27878920314 ns 27878533189 ns          1
BM_ImprovedSieveBitset/16777216  57179037827 ns 57178259858 ns          1
</pre>
