#ifndef BINARY_SEARCH_TREE_COMMON_H
#define BINARY_SEARCH_TREE_COMMON_H

#include "rebalance/rebalance.h"
#include "traversal/traversal.h"

template <typename Node>
void FreeTree(Node* root) {
  if (root == nullptr) return;
  FreeTree(root->left);
  FreeTree(root->right);
  delete root;
}

template <typename Node>
int TreeSize(Node* root) {
  if (root == nullptr) return 0;
  return 1 + TreeSize(root->left) + TreeSize(root->right);
}

#endif
