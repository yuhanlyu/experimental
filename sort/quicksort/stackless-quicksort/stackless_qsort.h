#ifndef STACKLESS_QSORT_H_
#define STACKLESS_QSORT_H_

#include <limits>
#include <utility>

// Stackless quicksort:
//    sort the array A[2..end - 1], assuming A[0], A[1], and A[end]
//    are modifiable and numeric_limits<T>::min() is smaller than all
//    values in A.
//
// For example:
// const int shift = 2;
// int A[size + shift + 1];
// StacklessQSort(A, size + shift + 1) will sort the 
// A[shift..shift + size - 1] (inclusively).
// The effect is the same as std::sort(A + shift, A + shift + size);
//
// This algorithm is from Lutz Michael Wegner's paper
// "A generalized, one-way, stackless quicksort,"
// BIT Numerical Mathematics 1987, Volume 27, Issue 1, pp 44-48
template <typename T>
void StacklessQSort(T A[], int end) {
  A[0] = A[1] = A[end] = std::numeric_limits<T>::min();
  for (int left = 2; left <= end;) {
    // A[left] is a stopper, an empty subfile.
    if (A[left] <= A[left - 1]) {
      A[left - 2] = A[left];
      left += 2;
      continue;
    }
    int j = left, i = left;
    for (T pivot = A[left];;) {
      // Find the next out of order position.
      while (pivot < A[++j])
        ;

      // A[j] is a stopeer, partition the current part is finished.
      if (A[j] <= A[left - 1]) {
        A[i] = pivot;
        break;
      }

      // A[j] is not a stopper.
      if (A[j] >= A[i - 1]) {
        // A[i] must be the maximum of the left part.
        A[i] = A[j];
      } else {
        A[i] = A[i - 1];
        A[i - 1] = A[j];
      }
      A[j] = A[++i];
    }
    if (left + 2 >= i) {
      A[left - 2] = A[j];
      A[j] = A[i - 1];
      left = i + 1;
    } else {
      std::swap(A[i - 1], A[j]);
    }
  }
}

#endif
