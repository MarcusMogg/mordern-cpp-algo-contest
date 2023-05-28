#pragma once

#include "lcsrc/lib/stlplus.h"

namespace leetcode::findthekthsmallestsumofamatrixwithsortedrows {

int Solve(const std::vector<std::vector<int>>& mat, int k);

namespace standard {
int Solve(const std::vector<std::vector<int>>& mat, int k);
}  // namespace standard

}  // namespace leetcode::findthekthsmallestsumofamatrixwithsortedrows