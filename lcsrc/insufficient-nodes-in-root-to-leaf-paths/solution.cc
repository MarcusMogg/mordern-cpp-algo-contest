#include "solution.h"

namespace leetcode::insufficientnodesinroottoleafpaths {

TreeNode* Solve(TreeNode* root, int limit) {
  // TODO(): your solution here
  return {};
}

namespace standard {

bool Traverse(TreeNode* cur, int sum, int limit) {
  sum = sum + cur->val;
  if (cur->left == nullptr && cur->right == nullptr) {
    return sum < limit;
  }
  bool need_delete = true;
  const auto check_and_delete = [&](auto& ptr) {
    if (ptr != nullptr) {
      if (Traverse(ptr, sum, limit)) {
        ptr = nullptr;
      } else {
        need_delete = false;
      }
    }
  };
  check_and_delete(cur->left);
  check_and_delete(cur->right);
  return need_delete;
}

TreeNode* Solve(TreeNode* root, int limit) {
  if (Traverse(root, 0, limit)) {
    return nullptr;
  }
  return root;
}
}  // namespace standard

}  // namespace leetcode::insufficientnodesinroottoleafpaths