#ifndef ROTATION_H
#define ROTATION_H

#include <algorithm>

inline int GCD(int a, int b) {
  while ((a %= b) && (b %= a))
    ;
  return a + b;
}

// Swap the subarray A[i..i+k-1] with A[j..j+k-1].
template <typename T>
inline void SwapSection(T A[], int i, int j, int k) {
  while (k-- > 0) {
    std::swap(A[i++], A[j++]);
  }
}

// Rotate an array circularly to the left by k positions
// This algorithm is from Jon Bentley's Programming Pearls.
template <typename T>
void JugglingBentley(T A[], int n, int k) {
  for (int i = 0, bound = GCD(n, k); i < bound; ++i) {
    int to = i, from = (i + k) % n, temp = A[i];
    do {
      A[to] = A[from];
      to = from;
      from = (from + k) % n;
    } while (from != i);
    A[to] = temp;
  }
}

// Rotate an array circularly to the left by k positions
// This algorithm is from
// Ching-Kuang Shene,
// An Analysis of Two In-Place Array Rotation Algorithms
// The Computer Journal (1997) 40 (9): 541-546.
template <typename T>
void JugglingShene(T A[], int n, int k) {
  for (int i = 0, bound = n; i < bound; ++i) {
    int to = i, from = (i + k) % n, temp = A[i];
    do {
      A[to] = A[from];
      to = from;
      if (from < bound) bound = from;
      from = (from + k) % n;
    } while (from != i);
    A[to] = temp;
  }
}

// Rotate an array circularly to the left by k positions
// This algorithm is from Jon Bentley's Programming Pearls.
template <typename T>
void RotateReverse(T A[], int n, int k) {
  std::reverse(A, A + k);
  std::reverse(A + k, A + n);
  std::reverse(A, A + n);
}

// Rotate an array circularly to the left by k positions
// This algorithm is from
// Ching-Kuang Shene,
// An Analysis of Two In-Place Array Rotation Algorithms
// The Computer Journal (1997) 40 (9): 541-546.
template <typename T>
void BlockSwapShene(T A[], int n, int k) {
  for (int left = 0, right = k, middle = k;;) {
    std::swap(A[left++], A[right++]);
    if (left == middle) {
      if (right == n) {
        return;
      }
      middle = right;
    } else if (right == n) {
      right = middle;
    }
  }
}

// Rotate an array circularly to the left by k positions
// This algorithm is from
// David Gries and Harlan Mills,
// Swapping sections.
// Technical Report TR 81-452, Cornell University.
template <typename T>
void BlockSwapGries(T A[], int n, int k) {
  int i = k;
  for (int j = n - k; i != j;) {
    if (i > j) {
      SwapSection(A, k - i, k, j);
      i -= j;
    } else {
      SwapSection(A, k - i, k + j - i, i);
      j -= i;
    }
  }
  SwapSection(A, k - i, k, i);
}

#endif
