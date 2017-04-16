#ifndef BINARY_SEARCH_TREE_COMMON_H
#define BINARY_SEARCH_TREE_COMMON_H

template <typename T>
void InorderTraverse(T* root, std::vector<typename T::value_type>& result) {
  if (root == nullptr) return;
  InorderTraverse(root->left, result);
  result.push_back(root->value);
  InorderTraverse(root->right, result);
}

#endif
