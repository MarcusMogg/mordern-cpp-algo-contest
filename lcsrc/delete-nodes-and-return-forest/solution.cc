#include "solution.h"

#include <cstddef>

namespace leetcode::deletenodesandreturnforest {

std::vector<TreeNode*> Solve(TreeNode* root, const std::vector<int>& to_delete) {
  // TODO(): your solution here
  return {};
}

namespace standard {
std::vector<TreeNode*> Solve(TreeNode* root, const std::vector<int>& to_delete) {
  std::vector<TreeNode*> res;
  std::set<int> todelete{to_delete.begin(), to_delete.end()};
  using TreePtr = TreeNode*;
  const auto dfs = [&res, &todelete](auto&& dfs, TreePtr& cur, bool deleted_par) {
    if (cur == nullptr) {
      return;
    }
    if (todelete.count(cur->val) == 0) {
      if (deleted_par) {
        res.emplace_back(cur);
      }
      deleted_par = false;
    } else {
      deleted_par = true;
    }
    if (cur->left) {
      dfs(dfs, cur->left, deleted_par);
    }
    if (cur->right) {
      dfs(dfs, cur->right, deleted_par);
    }
    if (deleted_par) {
      cur = nullptr;
    }
  };
  dfs(dfs, root, true);
  return res;
}
}  // namespace standard

}  // namespace leetcode::deletenodesandreturnforest