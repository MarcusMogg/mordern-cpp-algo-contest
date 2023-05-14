#pragma once

#include "lcsrc/lib/stlplus.h"

namespace leetcode::distantbarcodes {

std::vector<int> Solve(const std::vector<int>& barcodes);

namespace standard {
std::vector<int> Solve(const std::vector<int>& barcodes);
}  // namespace standard

}  // namespace leetcode::distantbarcodes