#include "solution.h"

#include <algorithm>
#include <limits>

namespace leetcode::maximumsumbstinbinarytree {

int Solve(TreeNode* root) {
  // TODO(): your solution here
  return {};
}

namespace standard {

std::tuple<bool, int, int, int> Traverse(TreeNode* root, int& max_sum) {
  if (root == nullptr) {
    return {true, std::numeric_limits<int>::max(), std::numeric_limits<int>::min(), 0};
  }
  int res = root->val;
  bool is_t = true;
  int cur_min = root->val;
  int cur_max = root->val;
  {
    auto [is_tree, min, max, sum] = Traverse(root->left, max_sum);
    if (!is_tree || max >= root->val) {
      is_t = false;
      res = 0;

    } else {
      res += sum;
      cur_min = std::min(min, cur_min);
    }
  }
  {
    auto [is_tree, min, max, sum] = Traverse(root->right, max_sum);
    if (!is_tree || min <= root->val) {
      is_t = false;
      res = 0;
    } else {
      res += sum;
      cur_max = std::max(max, cur_max);
    }
  }
  max_sum = std::max(max_sum, res);
  return {is_t, cur_min, cur_max, res};
}

int Solve(TreeNode* root) {
  int res = std::numeric_limits<int>::min();
  Traverse(root, res);
  return res;
}
}  // namespace standard

}  // namespace leetcode::maximumsumbstinbinarytree