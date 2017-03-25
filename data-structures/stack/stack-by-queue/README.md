Using two queues to implement a stack.
This solution is from Martin Hühne's paper
“On the Power of Several Queues”.
In: Theoretical Computer Science 113.1 (May 1993), pages 75–91.

When use two queues to implement a stack, push and pop will take O(sqrt(n))
amortized time, where n is the number of elements in the stack. Hence, the
solution is impractical.

Using k queues to implement a stack is also possible, and the time complexity
will become O(n^{1/k}) for push and pop.

## Benchmark
<pre>
-----------------------------------------------------------
Benchmark                    Time           CPU Iterations
-----------------------------------------------------------
BM_StackByQueuePush       1966 ns       1966 ns    1167950
BM_STLStackPush              2 ns          2 ns  295125925
BM_StackByQueueMix         528 ns        528 ns    1000000
BM_STLStackMix              56 ns         56 ns   12534633
</pre>
