# Biased binary search
## Background
Ordinary binary search always compare the target element with the mid point
and divide the array by the mid point. However, this approach will have high
misprediction rate when the elements are uniformly distributed, since the
result of comparision is true with probability around .5.

This module contains two variants of binary search:
1. Use conditional move to remove branch.  
Paul-Virak Khuong, Pat Morin  
[Array Layouts for Comparison-Based Searching](https://arxiv.org/abs/1509.05053)
1. Instead of picking the middle point, pick mid point of the first half.  
Gerth Stølting Brodal, Gabriel Moruz,  
[Skewed Binary Search Trees](https://www.doi.org/10.1007/11841036_63),  
Lecture Notes in Computer Science Volume 4168, 2006, pp 708-719

## Test method
A set of integers is generated uniformly at random and sorted. Then, generate
random number as target element to be searched in the sorted set. Since the
random number generation is included in the CPU time in the benchmark, I also
measure the running time of random number generation.

## Result
I compared the branch-free binary search, skewed binary search, C++ STL
lower\_bound, and bsearch in stdlib by measuring the running time of finding
an element in a sorted integer array whose elements are drawn from a uniform
distribution. The results are shown below:

<pre>
----------------------------------------------------------------------------------------
Benchmark                                                 Time           CPU Iterations
----------------------------------------------------------------------------------------
SearchBenchmark/Random/1048576                           15 ns         15 ns   45170766
SearchBenchmark/BranchfreeBinarySearch/1024              26 ns         26 ns   27312222
SearchBenchmark/BranchfreeBinarySearch/4096              29 ns         29 ns   24038807
SearchBenchmark/BranchfreeBinarySearch/16384             36 ns         36 ns   19684983
SearchBenchmark/BranchfreeBinarySearch/65536             51 ns         51 ns   13860796
SearchBenchmark/BranchfreeBinarySearch/262144            98 ns         98 ns    7238086
SearchBenchmark/BranchfreeBinarySearch/1048576          140 ns        140 ns    5091140
SearchBenchmark/BranchfreeBinarySearch/4194304          586 ns        586 ns    1263702
SearchBenchmark/BranchfreeBinarySearch/16777216         932 ns        932 ns     762211
SearchBenchmark/BranchfreeBinarySearch/67108864        1150 ns       1150 ns     620953
SearchBenchmark/BranchfreeBinarySearch/268435456       1363 ns       1363 ns     526331
SearchBenchmark/SkewedBinarySearch/1024                  60 ns         60 ns   10355621
SearchBenchmark/SkewedBinarySearch/4096                  68 ns         68 ns   10319222
SearchBenchmark/SkewedBinarySearch/16384                 77 ns         77 ns    9153474
SearchBenchmark/SkewedBinarySearch/65536                 88 ns         88 ns    7956752
SearchBenchmark/SkewedBinarySearch/262144               110 ns        110 ns    6346699
SearchBenchmark/SkewedBinarySearch/1048576              128 ns        128 ns    5253171
SearchBenchmark/SkewedBinarySearch/4194304              211 ns        211 ns    3347311
SearchBenchmark/SkewedBinarySearch/16777216             306 ns        306 ns    2266664
SearchBenchmark/SkewedBinarySearch/67108864             402 ns        402 ns    1763126
SearchBenchmark/SkewedBinarySearch/268435456            502 ns        502 ns    1000000
SearchBenchmark/STLSearch/1024                           65 ns         65 ns   10432752
SearchBenchmark/STLSearch/4096                           74 ns         74 ns    9568054
SearchBenchmark/STLSearch/16384                          86 ns         86 ns    8151415
SearchBenchmark/STLSearch/65536                         104 ns        104 ns    6618087
SearchBenchmark/STLSearch/262144                        143 ns        143 ns    4899108
SearchBenchmark/STLSearch/1048576                       174 ns        174 ns    4057186
SearchBenchmark/STLSearch/4194304                       387 ns        387 ns    1827747
SearchBenchmark/STLSearch/16777216                      639 ns        639 ns    1161262
SearchBenchmark/STLSearch/67108864                      829 ns        829 ns     930193
SearchBenchmark/STLSearch/268435456                    1100 ns       1100 ns     663793
SearchBenchmark/BSearch/1024                             64 ns         64 ns   10489409
SearchBenchmark/BSearch/4096                             72 ns         72 ns    9606502
SearchBenchmark/BSearch/16384                            85 ns         85 ns    8283490
SearchBenchmark/BSearch/65536                           103 ns        103 ns    6801083
SearchBenchmark/BSearch/262144                          142 ns        142 ns    4948072
SearchBenchmark/BSearch/1048576                         173 ns        173 ns    4092475
SearchBenchmark/BSearch/4194304                         387 ns        387 ns    1829945
SearchBenchmark/BSearch/16777216                        652 ns        652 ns    1143447
SearchBenchmark/BSearch/67108864                        851 ns        851 ns     873622
SearchBenchmark/BSearch/268435456                      1123 ns       1122 ns     632948
</pre>

The biased search is fastest method among all methods.

Compare STLSearch with SkewedBinarySearch when the set size is 1048576, the running
time of STLSearch is 210 - 51(random numbe generation) = 159, and the running
time of SkewedBinarySearch is 167 - 51 = 112. Hence, biased search method reduced
the running time by 30$.

### Result of perf stat
<pre>
BranchfreeBinarySearch
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
SkewedBinarySearch
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
