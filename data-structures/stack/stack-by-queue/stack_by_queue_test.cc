#include "stack_by_queue.h"

#include "gtest/gtest.h"

namespace {

TEST(StackByQueueTest, Push) {
  Stack<int> stack;
  for (int i = 0; i < 10; ++i) {
    stack.push(i);
    EXPECT_EQ(i, stack.top());
  }
}

TEST(StackByQueueTest, Pop) {
  Stack<int> stack;
  for (int i = 0; i < 10; ++i) {
    stack.push(i);
  }
  for (int i = 9; i >= 0; --i) {
    EXPECT_EQ(i, stack.top());
    stack.pop();
  }
}

}  // namespace
