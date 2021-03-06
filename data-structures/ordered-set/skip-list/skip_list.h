#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include <cstdlib>
#include <random>
#include <vector>

template <typename T>
struct SkipList {
 public:
  struct Node {
    using value_type = T;
    Node() = default;
    T value;
    Node* forward[];
  };

  void Insert(const T& x) {
    int new_level = random_level();
    // Grow at most one level.
    if (new_level > level) new_level = ++level;
    Node *cur = header, *new_node = NewNode(x, new_level);
    // Traverse each level above the new_level.
    for (int i = level - 1; i >= new_level; --i) {
      while (cur->forward[i] != nullptr && cur->forward[i]->value < x)
        cur = cur->forward[i];
    }
    // Traverse each level below the new_level and adjust the list.
    for (int i = new_level - 1; i >= 0; --i) {
      while (cur->forward[i] != nullptr && cur->forward[i]->value < x)
        cur = cur->forward[i];
      new_node->forward[i] = cur->forward[i];
      cur->forward[i] = new_node;
    }
  }

  bool Delete(const T& x) {
    Node *cur = header, *to_be_deleted = nullptr;
    for (int i = level - 1; i >= 0; --i) {
      while (cur->forward[i] != nullptr && cur->forward[i]->value < x)
        cur = cur->forward[i];
      if (cur->forward[i] != nullptr && cur->forward[i]->value == x) {
        if (i == 0) to_be_deleted = cur->forward[i];
        cur->forward[i] = cur->forward[i]->forward[i];
        if (header->forward[i] == nullptr) --level;
      }
    }
    if (to_be_deleted == nullptr) return false;
    std::free(to_be_deleted);
    return true;
  }

  void InorderTraverse(std::vector<T>& result) const {
    for (Node* cur = header->forward[0]; cur != nullptr;
         cur = cur->forward[0]) {
      result.push_back(cur->value);
    }
  }

  ~SkipList() {
    for (Node* cur = header, *next; cur != nullptr; cur = next) {
      next = cur->forward[0];
      free(cur);
    }
  }

 private:
  static int random_level() {
    static std::random_device random_device;
    static std::default_random_engine generator{random_device()};
    static std::uniform_int_distribution<unsigned int> distribution;
    unsigned int r{distribution(generator)};
    return r == 0 ? 33 : (__builtin_ctz(r) + 1);
  }

  static Node* NewNode(const T& x, int level) {
    Node* new_node =
        static_cast<Node*>(std::malloc(sizeof(Node) + sizeof(Node*) * level));
    new_node->value = x;
    return new_node;
  }

  // This is only used for the header.
  constexpr static int max_level = 33;
  Node* header = static_cast<Node*>(
      std::calloc(sizeof(Node) + max_level * sizeof(Node*), sizeof(char)));
  int level = 1;
};
#endif
