# Biased binary search
## Background
Ordinary binary search always compare the target element with the mid point
and divide the array by the mid point. However, this approach will have high
misprediction rate when the elements are uniformly distributed, since the
result of comparision is true with probability around .5. Thus, a better
approach is to divide the array unevenly, which I call biased search method.

I read this method from the following paper:
Gerth Stølting Brodal, Gabriel Moruz,  
[Skewed Binary Search Trees](https://www.doi.org/10.1007/11841036_63),  
Lecture Notes in Computer Science Volume 4168, 2006, pp 708-719

I also implemented a binary search based on conditional move to remove all
misprediction that is explained in the article -- [Retrospective on Binary Search and Comp{ress,ilat}ion](https://www.pvk.ca/Blog/2015/11/29/retrospective-on-binary-search-and-on-compression-slash-compilation/)

## Test method
A set of integers is generated uniformly at random and sorted. Then, generate
random number as target element to be searched in the sorted set. Since the
random number generation is included in the CPU time in the benchmark, I also
measure the running time of random number generation.

## Result
I compared my implementation of binary search, biased search, C++ STL
lower\_bound, and bsearch in stdlib by measuring the running time of finding
an element in a sorted integer array whose elements are drawn from a uniform
distribution. The results are shown below:

<pre>
------------------------------------------------------------------------------
Benchmark                                       Time           CPU Iterations
------------------------------------------------------------------------------
SearchBenchmark/Random/1048576                 15 ns         15 ns   45187055
SearchBenchmark/BinarySearch/1024              26 ns         26 ns   26619032
SearchBenchmark/BinarySearch/4096              29 ns         29 ns   23832465
SearchBenchmark/BinarySearch/16384             37 ns         37 ns   18973251
SearchBenchmark/BinarySearch/65536             53 ns         53 ns   12880652
SearchBenchmark/BinarySearch/262144           108 ns        108 ns    6573792
SearchBenchmark/BinarySearch/1048576          167 ns        167 ns    4128847
SearchBenchmark/BinarySearch/4194304          651 ns        651 ns    1134124
SearchBenchmark/BinarySearch/16777216         982 ns        982 ns     724530
SearchBenchmark/BinarySearch/67108864        1198 ns       1198 ns     593342
SearchBenchmark/BinarySearch/268435456       1406 ns       1406 ns     504907
SearchBenchmark/BiasedSearch/1024              59 ns         59 ns   11213908
SearchBenchmark/BiasedSearch/4096              67 ns         67 ns   10378944
SearchBenchmark/BiasedSearch/16384             76 ns         76 ns    9191853
SearchBenchmark/BiasedSearch/65536             86 ns         86 ns    8045438
SearchBenchmark/BiasedSearch/262144           110 ns        110 ns    6347804
SearchBenchmark/BiasedSearch/1048576          130 ns        130 ns    5276553
SearchBenchmark/BiasedSearch/4194304          206 ns        206 ns    3389488
SearchBenchmark/BiasedSearch/16777216         300 ns        300 ns    2326153
SearchBenchmark/BiasedSearch/67108864         392 ns        392 ns    1757196
SearchBenchmark/BiasedSearch/268435456        496 ns        496 ns    1420024
SearchBenchmark/STLSearch/1024                 66 ns         66 ns   10349370
SearchBenchmark/STLSearch/4096                 74 ns         74 ns    9450538
SearchBenchmark/STLSearch/16384                86 ns         86 ns    8079243
SearchBenchmark/STLSearch/65536               103 ns        103 ns    6753223
SearchBenchmark/STLSearch/262144              144 ns        144 ns    4822735
SearchBenchmark/STLSearch/1048576             177 ns        177 ns    3934067
SearchBenchmark/STLSearch/4194304             386 ns        386 ns    1813994
SearchBenchmark/STLSearch/16777216            640 ns        640 ns    1160343
SearchBenchmark/STLSearch/67108864            826 ns        826 ns     901772
SearchBenchmark/STLSearch/268435456          1092 ns       1092 ns     668420
SearchBenchmark/BSearch/1024                   64 ns         64 ns   10430009
SearchBenchmark/BSearch/4096                   72 ns         72 ns    9668074
SearchBenchmark/BSearch/16384                  85 ns         85 ns    8238533
SearchBenchmark/BSearch/65536                 101 ns        101 ns    6823913
SearchBenchmark/BSearch/262144                143 ns        143 ns    4875428
SearchBenchmark/BSearch/1048576               176 ns        176 ns    3913013
SearchBenchmark/BSearch/4194304               382 ns        382 ns    1841604
SearchBenchmark/BSearch/16777216              650 ns        650 ns    1146531
SearchBenchmark/BSearch/67108864              847 ns        847 ns     869768
SearchBenchmark/BSearch/268435456            1119 ns       1119 ns     642861
</pre>

The biased search is fastest method among all methods.

Compare STLSearch with BiasedSearch when the set size is 1048576, the running
time of STLSearch is 210 - 51(random numbe generation) = 159, and the running
time of BiasedSearch is 167 - 51 = 112. Hence, biased search method reduced
the running time by 30$.

### Result of perf stat
<pre>
BinarySearch
    33,540,985,687      cycles                                                        (30.70%)
    42,242,826,933      instructions              #    1.26  insn per cycle           (38.39%)
     5,152,687,213      branches                                                      (38.41%)
           611,133      branch-misses             #    0.01% of all branches          (38.54%)
       670,681,476      L1-dcache-load-misses     #   12.20% of all L1-dcache hits    (38.56%)
     5,496,622,147      L1-dcache-loads                                               (38.55%)
     2,752,714,197      L1-dcache-stores                                              (30.83%)
        45,309,220      LLC-load-misses           #   21.97% of all LL-cache hits     (30.82%)
       206,248,071      LLC-loads                                                     (30.81%)
        62,647,222      LLC-store-misses                                              (15.44%)
        97,472,863      LLC-stores                                                    (15.43%)
           566,223      branch-load-misses                                            (23.09%)
     5,246,602,875      branch-loads                                                  (30.75%)
BiasedSearch
    37,477,990,530      cycles                                                        (38.35%)
    41,707,176,142      instructions              #    1.11  insn per cycle           (46.05%)
     7,640,213,270      branches                                                      (46.09%)
       491,780,115      branch-misses             #    6.44% of all branches          (46.05%)
     1,533,415,822      L1-dcache-load-misses     #   31.41% of all L1-dcache hits    (46.16%)
     4,881,462,460      L1-dcache-loads                                               (46.32%)
     3,330,336,368      L1-dcache-stores                                              (30.88%)
       269,923,324      LLC-load-misses           #   27.41% of all LL-cache hits     (30.87%)
       984,597,365      LLC-loads                                                     (30.82%)
        54,174,347      LLC-store-misses                                              (15.42%)
        96,277,104      LLC-stores                                                    (15.45%)
       489,520,623      branch-load-misses                                            (23.06%)
     7,652,727,534      branch-loads                                                  (30.73%)
STLSearch
    33,765,237,076      cycles                                                        (38.46%)
    29,131,353,341      instructions              #    0.86  insn per cycle           (46.16%)
     5,156,833,291      branches                                                      (46.16%)
       474,271,947      branch-misses             #    9.20% of all branches          (46.16%)
     1,558,090,589      L1-dcache-load-misses     #   39.92% of all L1-dcache hits    (46.16%)
     3,902,742,001      L1-dcache-loads                                               (46.16%)
     2,730,539,544      L1-dcache-stores                                              (30.77%)
       323,592,976      LLC-load-misses           #   32.18% of all LL-cache hits     (30.84%)
     1,005,678,738      LLC-loads                                                     (30.82%)
        56,248,363      LLC-store-misses                                              (15.40%)
        96,206,538      LLC-stores                                                    (15.40%)
       473,922,338      branch-load-misses                                            (23.09%)
     5,137,926,768      branch-loads                                                  (30.77%)
BSearch
    33,343,142,903      cycles                                                        (38.43%)
    27,953,395,519      instructions              #    0.84  insn per cycle           (46.10%)
     5,290,587,196      branches                                                      (46.15%)
       450,016,837      branch-misses             #    8.51% of all branches          (46.19%)
     1,580,384,521      L1-dcache-load-misses     #   40.00% of all L1-dcache hits    (46.15%)
     3,950,583,215      L1-dcache-loads                                               (46.16%)
     2,727,716,048      L1-dcache-stores                                              (30.75%)
       335,720,820      LLC-load-misses           #   31.99% of all LL-cache hits     (30.82%)
     1,049,578,985      LLC-loads                                                     (30.90%)
        47,541,782      LLC-store-misses                                              (15.44%)
        80,188,457      LLC-stores                                                    (15.35%)
       452,680,318      branch-load-misses                                            (23.05%)
     5,085,179,040      branch-loads                                                  (30.70%)
</pre>
