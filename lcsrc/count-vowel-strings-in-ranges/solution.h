#pragma once

#include "lcsrc/lib/stlplus.h"

namespace leetcode::countvowelstringsinranges {

std::vector<int> Solve(
    const std::vector<std::string>& words, const std::vector<std::vector<int>>& queries);

namespace standard {
std::vector<int> Solve(
    const std::vector<std::string>& words, const std::vector<std::vector<int>>& queries);
}  // namespace standard

}  // namespace leetcode::countvowelstringsinranges