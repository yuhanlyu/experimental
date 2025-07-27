# Binary search
When the comparison is expensive, then the performance between different
implementations of binary search will be small. Thus, I only compare
the performance for integer type.

When the number of elements is not big, the time is dominated by the
branch misprediction, thus branchless version tends to be faster. However,
even if the source code does not use if-else, compiler may still use branch
in the assembly. Thus, determining which implementation is faster is hard.

When the number of elements is big, the time is dominated by the cache miss.
However, since the skewed binary search make speculation execution more
effective, the the skewed bianry search tends to be faster.
