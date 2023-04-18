#include "solution.h"

#include <algorithm>
#include <tuple>

namespace leetcode::maximumdifferencebetweennodeandancestor {

using Result = std::tuple<int, int, int>;

Result Minmax(TreeNode* root) {
  if (root == nullptr) {
    return {};
  }
  int minv = root->val;
  int maxv = root->val;
  int v = 0;

  const auto merge = [&minv, &maxv, &v, root](const Result& tmp) {
    minv = std::min(minv, std::get<0>(tmp));
    maxv = std::max(maxv, std::get<1>(tmp));
    v = std::max({
        v,
        std::abs(minv - root->val),
        std::abs(maxv - root->val),
        std::get<2>(tmp),
    });
  };

  if (root->left != nullptr) {
    merge(Minmax(root->left));
  }
  if (root->right != nullptr) {
    merge(Minmax(root->right));
  }
  return {minv, maxv, v};
}

int Solve(TreeNode* root) { return std::get<2>(Minmax(root)); }

namespace standard {
int Solve(TreeNode* root) { return std::get<2>(Minmax(root)); }
}  // namespace standard

}  // namespace leetcode::maximumdifferencebetweennodeandancestor