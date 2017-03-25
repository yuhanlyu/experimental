#ifndef ROTATION_H
#define ROTATION_H

// Rotate an array circularly to the left by k positions
// This algorithm is from Jon Bentley's Programming Pearls.
void JugglingBentley(int A[], int n, int k);

// Rotate an array circularly to the left by k positions
// This algorithm is from
// Ching-Kuang Shene,
// An Analysis of Two In-Place Array Rotation Algorithms
// The Computer Journal (1997) 40 (9): 541-546.
void JugglingShene(int A[], int n, int k);

// Rotate an array circularly to the left by k positions
// This algorithm is from Jon Bentley's Programming Pearls.
void RotateReverse(int A[], int n, int k);

// Rotate an array circularly to the left by k positions
// This algorithm is from
// Ching-Kuang Shene,
// An Analysis of Two In-Place Array Rotation Algorithms
// The Computer Journal (1997) 40 (9): 541-546.
void BlockSwapShene(int A[], int n, int k);

// Rotate an array circularly to the left by k positions
// This algorithm is from
// David Gries and Harlan Mills,
// Swapping sections.
// Technical Report TR 81-452, Cornell University.
void BlockSwapGries(int A[], int n, int k);

#endif
