#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

// Returns an iterator pointing to the first element in the range [first, last)
// that is not less than (i.e. greater or equal to) value. The range [first,
// last) must be ordered. This is a standard binary search algorithm.
template <typename T>
const T* BinarySearch(const T* first, const T* last, T x) {
  for (int length = last - first; length > 0;) {
    int half = length >> 1;
    const T* middle = first + half;
    if (*middle < x) {
      first = middle + 1;
      length -= half + 1;
    } else {
      length = half;
    }
  }
  return first;
}

// Returns an iterator pointing to the first element in the range [first, last)
// that is not less than (i.e. greater or equal to) value. The range [first,
// last) must be ordered. This algorithm is from the following paper:
// Gerth Stølting Brodal, Gabriel Moruz,Skewed Binary Search Trees,
// Lecture Notes in Computer Science Volume 4168, 2006, pp 708-719
template <typename T>
const T* BiasedBinarySearch(const T* first, const T* last, T x) {
  for (int length = last - first; length > 0;) {
    int half = length >> 2;
    const T* middle = first + half;
    if (*middle < x) {
      first = middle + 1;
      length -= half + 1;
    } else {
      length = half;
    }
  }
  return first;
}

#endif
