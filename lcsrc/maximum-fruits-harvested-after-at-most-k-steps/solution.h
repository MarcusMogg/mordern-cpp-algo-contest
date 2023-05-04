#pragma once

#include "lcsrc/lib/stlplus.h"

namespace leetcode::maximumfruitsharvestedafteratmostksteps {

int Solve(const std::vector<std::vector<int>>& fruits, int startPos, int k);

namespace standard {
int Solve(const std::vector<std::vector<int>>& fruits, int startPos, int k);
}  // namespace standard

}  // namespace leetcode::maximumfruitsharvestedafteratmostksteps