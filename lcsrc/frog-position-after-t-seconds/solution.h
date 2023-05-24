#pragma once

#include "lcsrc/lib/stlplus.h"

namespace leetcode::frogpositionaftertseconds {

double Solve(int n, const std::vector<std::vector<int>>& edges, int t, int target);

namespace standard {
double Solve(int n, const std::vector<std::vector<int>>& edges, int t, int target);
}  // namespace standard

}  // namespace leetcode::frogpositionaftertseconds