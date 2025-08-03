# Binary search
When the comparison is expensive, then the performance between different
implementations of binary search will be small. Thus, I only compare
the performance for integer type.

The performance difference in various binary search implementation is usually
due to the usage of CMOV by the compiler. Thus, I used cmov-converter = false
flag to disable CMOV to get more stable result. CMOV does not help when the
number of elements is large.

Moreover, for binary search implementations that always reduce the range by
exactly half, searching over an array of a length that is power of two leads
to higher cache miss due to competition,and make benchmark misleading. Thus,
the benchmark intentionally use arrays of lenghts that are a prime numbers.

Overall, when the number of elements is not big, the time is dominated by the
branch misprediction. When the number of elements is big, the time is dominated
by the cache miss. Since I only test random input, predicting which subtree to
prefetch is hard for the hardware except for the skewed binary search. However,
skewed binary search will need more comparison, so skewed binary search will be
slower for types with complicated comparison.
