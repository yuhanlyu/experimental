# Biased binary search
## Background
Ordinary binary search always compare the target element with the mid point
and divide the array by the mid point. However, this approach will have high
misprediction rate when the elements are uniformly distributed, since the
result of comparision is true with probability around .5. Thus, a better
approach is to divide the array unevenly, which I call biased search method.

I read this method from the following paper:
Gerth Stølting Brodal, Gabriel Moruz,Skewed Binary Search Trees,
Lecture Notes in Computer Science Volume 4168, 2006, pp 708-719

## Test method
A set of integers is generated uniformly at random and sorted. Then, generate
random number as target element to be searched in the sorted set. Since the
random number generation is included in the CPU time in the benchmark, I also
measure the running time of random number generation.

## Result
I compared my implementation of binary search, biased searhc with STL
lower\_bound and bsearch in stdlib by measuring the running time of finding
an element in a sorted integer array whose elements are drawn from a uniform
distribution. The result is shown below:

----------------------------------------------------------------------------
Benchmark                                     Time           CPU Iterations
----------------------------------------------------------------------------
SearchBenchmark/Random/1048576               51 ns         51 ns   13827433
SearchBenchmark/BinarySearch/1024            99 ns         99 ns    7050898
SearchBenchmark/BinarySearch/4096           109 ns        109 ns    6450624
SearchBenchmark/BinarySearch/16384          122 ns        122 ns    5757476
SearchBenchmark/BinarySearch/65536          141 ns        141 ns    4960329
SearchBenchmark/BinarySearch/262144         183 ns        183 ns    3828184
SearchBenchmark/BinarySearch/1048576        212 ns        212 ns    3293893
SearchBenchmark/BiasedSearch/1024            92 ns         92 ns    7605249
SearchBenchmark/BiasedSearch/4096           102 ns        102 ns    6885205
SearchBenchmark/BiasedSearch/16384          111 ns        111 ns    6287143
SearchBenchmark/BiasedSearch/65536          123 ns        123 ns    5697893
SearchBenchmark/BiasedSearch/262144         147 ns        147 ns    4782029
SearchBenchmark/BiasedSearch/1048576        167 ns        167 ns    4184260
SearchBenchmark/STLSearch/1024               98 ns         98 ns    7128321
SearchBenchmark/STLSearch/4096              107 ns        107 ns    6525206
SearchBenchmark/STLSearch/16384             122 ns        122 ns    5823726
SearchBenchmark/STLSearch/65536             139 ns        139 ns    4865778
SearchBenchmark/STLSearch/262144            181 ns        181 ns    3884047
SearchBenchmark/STLSearch/1048576           210 ns        210 ns    3327416
SearchBenchmark/BSearch/1024                101 ns        101 ns    6943504
SearchBenchmark/BSearch/4096                110 ns        110 ns    6400934
SearchBenchmark/BSearch/16384               122 ns        122 ns    5742203
SearchBenchmark/BSearch/65536               141 ns        141 ns    4960557
SearchBenchmark/BSearch/262144              182 ns        182 ns    3844379
SearchBenchmark/BSearch/1048576             212 ns        212 ns    3304502

The biased search is fastest method among all methods.

Compare STLSearch with BiasedSearch when the set size is 1048576, the running
time of STLSearch is 210 - 51(random numbe generation) = 159, and the running
time of BiasedSearch is 167 - 51 = 112. Hence, biased search method reduced
the running time by 30$.

### Result of perf stat
Here is the perf stat for biased search

      45499.903695      task-clock (msec)         #    1.000 CPUs utilized          
                32      context-switches          #    0.001 K/sec                  
                 0      cpu-migrations            #    0.000 K/sec                  
               639      page-faults               #    0.014 K/sec                  
   190,515,911,300      cycles                    #    4.187 GHz                    
   164,462,580,111      instructions              #    0.86  insn per cycle         
    30,552,200,918      branches                  #  671.478 M/sec                  
     2,978,081,010      branch-misses             #    9.75% of all branches 

Here is the perf stat for binary search

      50629.590220      task-clock (msec)         #    1.000 CPUs utilized          
                24      context-switches          #    0.000 K/sec                  
                 0      cpu-migrations            #    0.000 K/sec                  
               640      page-faults               #    0.013 K/sec                  
   211,601,286,770      cycles                    #    4.179 GHz                    
   114,467,394,551      instructions              #    0.54  insn per cycle         
    19,870,041,254      branches                  #  392.459 M/sec                  
     3,175,483,649      branch-misses             #   15.98% of all branches        

Here is the perf stat for STL lower\_bound

      49887.583328      task-clock (msec)         #    1.000 CPUs utilized          
                33      context-switches          #    0.001 K/sec                  
                 0      cpu-migrations            #    0.000 K/sec                  
               641      page-faults               #    0.013 K/sec                  
   208,814,333,106      cycles                    #    4.186 GHz                    
   108,836,166,274      instructions              #    0.52  insn per cycle         
    20,202,816,406      branches                  #  404.967 M/sec                  
     3,240,770,704      branch-misses             #   16.04% of all branches      

Here is the perf stat for stdlib bsearch

      50553.219060      task-clock (msec)         #    1.000 CPUs utilized          
                22      context-switches          #    0.000 K/sec                  
                 0      cpu-migrations            #    0.000 K/sec                  
               640      page-faults               #    0.013 K/sec                  
   211,599,881,216      cycles                    #    4.186 GHz                    
   103,908,539,111      instructions              #    0.49  insn per cycle         
    21,338,853,452      branches                  #  422.107 M/sec                  
     3,183,131,604      branch-misses             #   14.92% of all branches        

