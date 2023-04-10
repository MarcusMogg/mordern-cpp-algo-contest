#include "solution.h"

#include <algorithm>
#include <ranges>
#include <vector>

#include "lcsrc/lib/stlplus.h"

namespace leetcode::twosum {
using namespace std::ranges::views;
using namespace leetcode::lib;

namespace detail {

// n^2
std::vector<int> Solve1(const std::vector<int>& nums, const int& target) {
  const auto find_target = [&nums, target](auto&& cur) {
    return std::vector{
        static_cast<int>(cur - nums.begin()),
        static_cast<int>(std::find(cur + 1, nums.end(), target - *cur) - nums.begin()),
    };
  };
  const auto check_second = [&nums](auto&& p) { return p[1] < nums.size(); };
  const auto res = iota(nums.begin(), nums.end())          //
                   | transform(find_target)                //
                   | filter(check_second)                  //
                   | take(1)                               //
                   | to<std::vector<std::vector<int>>>();  // c++23
  return res[0];
}

// n^2
std::vector<int> Solve2(const std::vector<int>& nums, const int& target) {
  const auto find_target = [&nums, target](auto&& cur) {
    return std::vector{
        static_cast<int>(cur - nums.begin()),
        static_cast<int>(std::find(cur + 1, nums.end(), target - *cur) - nums.begin()),
    };
  };
  const auto check_second = [&nums](auto&& p) { return p[1] < nums.size(); };
  return iota(nums.begin(), nums.end())  //
         | transform(find_target)        //
         | filter(check_second)          //
         | take(1)                       //
         | join                          //
         | to<std::vector<int>>();       // c++23
}

// n*logn
std::vector<int> Solve3(const std::vector<int>& nums, const int& target) {
  const auto find_target = [&nums, target](auto&& cur) {
    return std::vector{
        static_cast<int>(cur - nums.begin()),
        static_cast<int>(std::upper_bound(cur + 1, nums.end(), target - *cur) - nums.begin()) - 1,
    };
  };
  const auto check_second = [&nums, target](auto&& p) {
    return p[1] < nums.size() && nums[p[0]] + nums[p[1]] == target;
  };
  return iota(nums.begin(), nums.end())  //
         | transform(find_target)        //
         | filter(check_second)          //
         | take(1)                       //
         | join                          //
         | to<std::vector<int>>();       // c++23
}
// n
std::vector<int> Solve4(const std::vector<int>& nums, const int& target) {
  const auto find_target = [&nums, target](auto&& cur) {
    return std::vector{
        static_cast<int>(cur - nums.begin()),
        static_cast<int>(std::upper_bound(cur + 1, nums.end(), target - *cur) - nums.begin()) - 1,
    };
  };
  const auto check_second = [&nums, target](auto&& p) {
    return p[1] < nums.size() && nums[p[0]] + nums[p[1]] == target;
  };
  return iota(nums.begin(), nums.end())  //
         | transform(find_target)        //
         | filter(check_second)          //
         | take(1)                       //
         | join                          //
         | to<std::vector<int>>();       // c++23
}
}  // namespace detail

std::vector<int> Solve(const std::vector<int>& nums, const int& target) {
  return detail::Solve3(nums, target);
}

namespace standard {
std::vector<int> Solve(const std::vector<int>& /*unused*/, const int& /*unused*/) {
  // TODO(): official answer here
  return {};
}
}  // namespace standard
}  // namespace leetcode::twosum