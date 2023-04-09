#include "solution.h"

#include <algorithm>
#include <ranges>
#include <vector>

namespace leetcode::twosum {
std::vector<int> Solve(const std::vector<int>& nums, const int& target) {
  using namespace std::ranges::views;
  const auto find_target = [&nums, target](auto&& cur) {
    return std::vector{
        static_cast<int>(cur - nums.begin()),
        static_cast<int>(std::find(cur + 1, nums.end(), target - *cur) - nums.begin()),
    };
  };
  const auto check_second = [&nums](auto&& p) { return p[1] < nums.size(); };
  for (const auto&& res :
       iota(nums.begin(), nums.end()) | transform(find_target) | filter(check_second)) {
    return res;
  }
  return {};
}

namespace standard {
std::vector<int> Solve(const std::vector<int>& /*unused*/, const int& /*unused*/) {
  // TODO(): official answer here
  return {};
}
}  // namespace standard
}  // namespace leetcode::twosum