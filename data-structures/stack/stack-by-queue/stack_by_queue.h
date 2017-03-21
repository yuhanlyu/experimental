#ifndef STACK_BY_QUEUE_H
#define STACK_BY_QUEUE_H

#include <queue>

// This solution is from Martin Hühne's paper
// “On the Power of Several Queues”.
// In: Theoretical Computer Science 113.1 (May 1993), pages 75–91.
template <typename T>
class Stack {
 public:
  void push(const T& x) {
    first.push(x);
    for (int i = first.size() - 1; i > 0; --i) {
      first.push(first.front());
      first.pop();
    }
    if (first.size() * first.size() > second.size()) {
      while (!second.empty()) {
        first.push(second.front());
        second.pop();
      }
      first.swap(second);
    }
  }

  void pop() { !first.empty() ? first.pop() : second.pop(); }

  T& top() { return !first.empty() ? first.front() : second.front(); }

  bool empty() const { return first.empty() && second.empty(); }

 private:
  std::queue<T> first;
  std::queue<T> second;
};

#endif
