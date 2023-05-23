#pragma once

#include "lcsrc/lib/stlplus.h"

namespace leetcode::largestvaluesfromlabels {

int Solve(
    const std::vector<int>& values, const std::vector<int>& labels, int numWanted, int useLimit);

namespace standard {
int Solve(
    const std::vector<int>& values, const std::vector<int>& labels, int numWanted, int useLimit);
}  // namespace standard

}  // namespace leetcode::largestvaluesfromlabels