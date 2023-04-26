#pragma once

#include "lcsrc/lib/stlplus.h"

namespace leetcode::maximumsumoftwononoverlappingsubarrays {

int Solve(const std::vector<int>& nums , int firstLen , int secondLen );

namespace standard {
int Solve(const std::vector<int>& nums , int firstLen , int secondLen );
}  // namespace standard

}  // namespace leetcode::maximumsumoftwononoverlappingsubarrays