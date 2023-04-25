#pragma once

#include "lcsrc/lib/stlplus.h"

namespace leetcode::sortthepeople {

std::vector<std::string> Solve(const std::vector<std::string>& names , const std::vector<int>& heights );

namespace standard {
std::vector<std::string> Solve(const std::vector<std::string>& names , const std::vector<int>& heights );
}  // namespace standard

}  // namespace leetcode::sortthepeople