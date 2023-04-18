#pragma once

#include <algorithm>
#include <iostream>
#include <queue>

template <class T>
struct TreeNodeTemp {
  T val;
  TreeNodeTemp* left;
  TreeNodeTemp* right;
  TreeNodeTemp() : val(T{}), left(nullptr), right(nullptr) {}
  explicit TreeNodeTemp(T x) : val(x), left(nullptr), right(nullptr) {}
  TreeNodeTemp(T x, TreeNodeTemp* left, TreeNodeTemp* right) : val(x), left(left), right(right) {}

  TreeNodeTemp(TreeNodeTemp&& rhs) noexcept : val(T{}), left(nullptr), right(nullptr) {
    std::swap(rhs.val, val);
    std::swap(rhs.left, left);
    std::swap(rhs.right, right);
  }
  TreeNodeTemp(TreeNodeTemp& rhs) noexcept = default;

  ~TreeNodeTemp() {
    // delete nullptr is safe
    delete left;
    delete right;
  }
};

struct TreeNode {
  using T = int;
  T val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(T{}), left(nullptr), right(nullptr) {}
  explicit TreeNode(T x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(T x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}

  TreeNode(TreeNode&& rhs) noexcept : val(T{}), left(nullptr), right(nullptr) {
    std::swap(rhs.val, val);
    std::swap(rhs.left, left);
    std::swap(rhs.right, right);
  }
  TreeNode(TreeNode& rhs) noexcept = default;

  ~TreeNode() {
    // delete nullptr is safe
    delete left;
    delete right;
  }
};
