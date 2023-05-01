#pragma once

#include "lcsrc/lib/stlplus.h"

namespace leetcode::timeneededtoinformallemployees {

int Solve(int n , int headID , const std::vector<int>& manager , const std::vector<int>& informTime );

namespace standard {
int Solve(int n , int headID , const std::vector<int>& manager , const std::vector<int>& informTime );
}  // namespace standard

}  // namespace leetcode::timeneededtoinformallemployees