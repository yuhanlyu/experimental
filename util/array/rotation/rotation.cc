#include "rotation.h"

#include <algorithm>

namespace {

inline int GCD(int a, int b) {
  while ((a %= b) && (b %= a))
    ;
  return a + b;
}

// Swap the subarray A[i..i+k-1] with A[j..j+k-1].
inline void SwapSection(int A[], int i, int j, int k) {
  while (k-- > 0) {
    int temp = A[i];
    A[i++] = A[j];
    A[j++] = temp;
  }
}

}  // namespace

void JugglingBentley(int A[], int n, int k) {
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

void JugglingShene(int A[], int n, int k) {
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

void RotateReverse(int A[], int n, int k) {
	std::reverse(A, A + k);
	std::reverse(A + k, A + n);
	std::reverse(A, A + n);
}

void BlockSwapShene(int A[], int n, int k) {
  for (int left = 0, right = k, middle = k;;) {
    int temp = A[left];
    A[left++] = A[right];
    A[right++] = temp;
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

void BlockSwapGries(int A[], int n, int k) {
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
