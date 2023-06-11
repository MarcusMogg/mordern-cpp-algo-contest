#pragma once

#include "lcsrc/lib/stlplus.h"

namespace leetcode::comparestringsbyfrequencyofthesmallestcharacter {

std::vector<int> Solve(
    const std::vector<std::string>& queries, const std::vector<std::string>& words);

namespace standard {
std::vector<int> Solve(
    const std::vector<std::string>& queries, const std::vector<std::string>& words);
}  // namespace standard

}  // namespace leetcode::comparestringsbyfrequencyofthesmallestcharacter