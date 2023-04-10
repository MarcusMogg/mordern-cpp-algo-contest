#include "solution.h"

#include <algorithm>
#include <ranges>
#include <vector>

#include "lcsrc/lib/stlplus.h"

namespace leetcode::twosum {
using namespace std::ranges::views;
using namespace leetcode::lib;

std::vector<int> Solve(const std::vector<int>& nums, const int& target) {
  const auto find_target = [&nums, target](auto&& cur) {
    return std::vector{
        static_cast<int>(cur - nums.begin()),
        static_cast<int>(std::find(cur + 1, nums.end(), target - *cur) - nums.begin()),
    };
  };
  const auto check_second = [&nums](auto&& p) { return p[1] < nums.size(); };
  const auto res = iota(nums.begin(), nums.end())  //
                   | transform(find_target)        //
                   | filter(check_second)          //
                   | take(1)                       //
                   | to<std::vector<std::vector<int>>>();
  return res[0];
}

namespace standard {
std::vector<int> Solve(const std::vector<int>& /*unused*/, const int& /*unused*/) {
  // TODO(): official answer here
  return {};
}
}  // namespace standard
}  // namespace leetcode::twosum