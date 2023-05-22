#pragma once

#include "lcsrc/lib/stlplus.h"

namespace leetcode::insufficientnodesinroottoleafpaths {

TreeNode* Solve(TreeNode* root, int limit);

namespace standard {
TreeNode* Solve(TreeNode* root, int limit);
}  // namespace standard

}  // namespace leetcode::insufficientnodesinroottoleafpaths