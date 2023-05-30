#pragma once

#include "lcsrc/lib/stlplus.h"

namespace leetcode::deletenodesandreturnforest {

std::vector<TreeNode*> Solve(TreeNode* root, const std::vector<int>& to_delete);

namespace standard {
std::vector<TreeNode*> Solve(TreeNode* root, const std::vector<int>& to_delete);
}  // namespace standard

}  // namespace leetcode::deletenodesandreturnforest