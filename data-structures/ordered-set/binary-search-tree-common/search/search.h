#ifndef BINARY_SEARCH_TREE_SEARCH_H
#define BINARY_SEARCH_TREE_SEARCH_H

template <typename Node>
const typename Node::value_type* Search(const Node* root,
                                        const typename Node::value_type& x) {
  while (root != nullptr && root->value != x) {
    root = x < root->value ? root->left : root->right;
  }
  return root == nullptr ? nullptr : &root->value;
}

template <typename Node>
const typename Node::value_type* FastSearch(
    const Node* root, const typename Node::value_type& x) {
  const Node* candidate = nullptr;
  while (root != nullptr) {
    if (x < root->value) {
      root = root->left;
    } else {
      candidate = root;
      root = root->right;
    }
  }
  if (candidate == nullptr) return nullptr;
  return candidate->value == x ? &candidate->value : nullptr;
}

#endif
