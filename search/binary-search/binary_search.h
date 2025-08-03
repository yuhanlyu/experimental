#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

#include <bit>
#include <cstddef>

// Returns an iterator pointing to the first element in the range [first, last)
// that is not less than (i.e. greater or equal to) value. The range [first,
// last) must be ordered. This is binary search implementation used by libc++.
template <typename T>
__attribute((hot)) const T* BinarySearch(const T* first, const T* last, T x) {
  for (std::ptrdiff_t length = last - first; length > 0;) {
    const std::ptrdiff_t half = length >> 1;
    if (const T* middle = first + half; *middle < x) {
      first = ++middle;
      length -= half + 1;
    } else
      length = half;
  }
  return first;
}

// Returns an iterator pointing to the first element in the range [first, last)
// that is not less than (i.e. greater or equal to) value. The range [first,
// last) must be ordered. This differs from standard binary search alrogithm
// in that length is decreased slower by one.
template <typename T>
__attribute((hot)) const T* BinarySearch1(const T* first, const T* last, T x) {
  for (std::ptrdiff_t length = last - first, half; length > 0; length = half) {
    half = length >> 1;
    first += (half + (length & 1LL)) * (first[half] < x);
  }
  return first;
}

// Returns an iterator pointing to the first element in the range [first, last)
// that is not less than (i.e. greater or equal to) value. The range [first,
// last) must be ordered. This differs from standard binary search alrogithm
// in that length is decreased slower by one.
template <typename T>
__attribute((hot)) const T* BinarySearch2(const T* first, const T* last, T x) {
  for (std::ptrdiff_t length = last - first, half; length > 0; length = half) {
    half = length >> 1;
    first += (length - half) * (first[half] < x);
  }
  return first;
}

// Returns an iterator pointing to the first element in the range [first, last)
// that is not less than (i.e. greater or equal to) value. The range [first,
// last) must be ordered. This differs from standard binary search alrogithm
// in that length is decreased slower by one.
template <typename T>
__attribute((hot)) const T* BinarySearch3(const T* first, const T* last, T x) {
  if (first == last) return first;
  // Since length is updated to length -= half, the loop termination condition
  // must be length > 1.
  for (std::ptrdiff_t length = last - first, half; length > 1; length -= half) {
    half = length >> 1;
    first += half * (first[half] < x);
  }
  // Since the loop terminates with length = 1, we need additional check.
  return first + (*first < x);
}

// Returns an iterator pointing to the first element in the range [first, last)
// that is not less than (i.e. greater or equal to) value. The range [first,
// last) must be ordered. This differs from standard binary search alrogithm
// in that length is decreased slower by one.
// This method is called Shar's method in The Art of Computer Programming
// volume 3 Exercise 6.2.1-12.
template <typename T>
__attribute((hot)) const T* Shar1(const T* first, const T* last, T x) {
  if (last == first) return first;
  std::ptrdiff_t length = last - first;
  if (length == 1) return first + (*first < x);
  const std::ptrdiff_t nearest_power_of_two =
      1ul << (std::bit_width(static_cast<unsigned long>(length)) - 1);
  std::ptrdiff_t base =
      (first[length >> 1] < x) ? length - nearest_power_of_two : -1;
  for (length = nearest_power_of_two >> 1; length != 0; length >>= 1) {
    base += length * (first[base + length] < x);
  }
  return first + (base + 1);
}

// Returns an iterator pointing to the first element in the range [first, last)
// that is not less than (i.e. greater or equal to) value. The range [first,
// last) must be ordered. This differs from standard binary search alrogithm
// in that length is decreased slower by one.
// This method is called Shar's method in The Art of Computer Programming
// volume 3 Exercise 6.2.1-12.
template <typename T>
__attribute((hot)) const T* Shar2(const T* first, const T* last, T x) {
  if (last == first) return first;
  std::ptrdiff_t length = last - first;
  if (length == 1) return first + (*first < x);
  const std::ptrdiff_t nearest_power_of_two =
      1ul << (std::bit_width(static_cast<unsigned long>(length)) - 1);
  std::ptrdiff_t remaining = length - nearest_power_of_two;
  if (const int* middle = first + remaining; *middle < x) first = middle;
  for (length = nearest_power_of_two; length > 1;) {
    length = length >> 1;
    first += length * (first[length] < x);
  }
  return first + (*first < x);
}

// Returns an iterator pointing to the first element in the range [first, last)
// that is not less than (i.e. greater or equal to) value. The range [first,
// last) must be ordered. This algorithm is from the following paper:
// Amr Elmasry and Jyrki Katajainen, Branchless Search Programs
// Experimental Algorithms. SEA 2013. Lecture Notes in Computer Science, vol
// 7933
template <typename T>
__attribute((hot)) const T* SkewedBinarySearch(const T* first, const T* last,
                                               T x) {
  for (std::ptrdiff_t length = last - first; length > 0;) {
    const std::ptrdiff_t half = length >> 2;
    if (const T* middle = first + half; *middle < x) {
      first = ++middle;
      length -= half + 1;
    } else
      length = half;
  }
  return first;
}

#define STEP(power_of_two) \
  case power_of_two:       \
    base += (power_of_two) * (first[base + (power_of_two)] < x)

template <typename T>
__attribute((hot)) const T* SharUnroll(const T* first, const T* last, T x) {
  if (last == first) return first;
  std::ptrdiff_t length = last - first;
  if (length == 1) return first + (*first < x);
  const int log = std::bit_width(static_cast<std::size_t>(length));
  const std::ptrdiff_t nearest_power_of_two = 1ul << (log - 1);
  std::ptrdiff_t base =
      (first[length >> 1] < x) ? length - nearest_power_of_two : -1;
  switch (nearest_power_of_two >> 1) {
    STEP(1073741824);
    STEP(536870912);
    STEP(268435456);
    STEP(134217728);
    STEP(67108864);
    STEP(33554432);
    STEP(16777216);
    STEP(8388608);
    STEP(4194304);
    STEP(2097152);
    STEP(1048576);
    STEP(524288);
    STEP(262144);
    STEP(131072);
    STEP(65536);
    STEP(32768);
    STEP(16384);
    STEP(8192);
    STEP(4096);
    STEP(2048);
    STEP(1024);
    STEP(512);
    STEP(256);
    STEP(128);
    STEP(64);
    STEP(32);
    STEP(16);
    STEP(8);
    STEP(4);
    STEP(2);
    STEP(1);
  }
  return first + (base + 1);
}
#endif
