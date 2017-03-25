#ifndef FIB_H
#define FIB_H
#include <cstdint>

// Computing Fibonacci number by using
// F(2n) = F(n)^2 + F(n+1)^2 and F(2n+1) = 2F(n)F(n+1) + F(n+1)^2
// This algorithm is from Joseph Shortt's paper
// An interative program to calculate fibonacci numbers in O(log n) arithmetic
// operations, Information Processing Letters Volume 7, Issue 6,
// October 1978, Pages 299-303
int64_t Doubling(int32_t n);

// This function computes the n-th fibonacci number, where n should be a
// non-negative number
// This algorithm is from L.F. Johnsonn's paper:
// Tumble, a fast simple iteration algorithm for Fibonacci,
// Information Processing Letters Volume 89, Issue 4, 28 February 2004,
// Pages 187-189
int64_t Tumble(int32_t n);

// Ordinary way of computing fibonacci number
int64_t Iterative(int32_t n);

// Q-matrix method
int64_t QMatrix(int32_t n);

#endif
