#include "solution.h"

#include <algorithm>
#include <functional>
#include <iterator>
#include <ranges>
#include <type_traits>
#include <vector>

namespace leetcode::maximumsumoftwononoverlappingsubarrays {

using namespace std::ranges;

int Solve(const std::vector<int>& nums, int firstLen, int secondLen) {
  std::vector<int> sum(nums.size() + 1, 0);
  std::ranges::transform(nums, sum, sum.begin() + 1, std::plus<>());

  const auto calculate_max = [&nums, &sum](int first, int second) {
    int res = 0;
    std::vector<int> l_max_value(nums.size(), 0);
    int r_max_value = 0;

    for (int i : views::iota(first, static_cast<int>(nums.size()))) {
      l_max_value[i] = std::max(l_max_value[i - 1], sum[i] - sum[i - first]);
    }
    for (int i = static_cast<int>(nums.size()) - second; i > 0; --i) {
      r_max_value = std::max(r_max_value, sum[i + second] - sum[i]);
      res = std::max(res, r_max_value + l_max_value[i]);
    }
    return res;
  };

  return std::max(calculate_max(firstLen, secondLen), calculate_max(secondLen, firstLen));
}

namespace standard {
int Solve(const std::vector<int>& nums, int firstLen, int secondLen) {
  std::vector<int> sum(nums.size() + 1, 0);
  for (int i = 0; i < nums.size(); i++) {
    sum[i + 1] = sum[i] + nums[i];
  }

  const auto calculate_max = [&nums, &sum](int first, int second) {
    int res = 0;
    std::vector<int> l_max_value(nums.size(), 0);
    int r_max_value = 0;

    for (int i = first; i < nums.size(); ++i) {
      l_max_value[i] = std::max(l_max_value[i - 1], sum[i] - sum[i - first]);
    }
    for (int i = static_cast<int>(nums.size()) - second; i > 0; --i) {
      r_max_value = std::max(r_max_value, sum[i + second] - sum[i]);
      res = std::max(res, r_max_value + l_max_value[i]);
    }
    return res;
  };

  return std::max(calculate_max(firstLen, secondLen), calculate_max(secondLen, firstLen));
}
}  // namespace standard

}  // namespace leetcode::maximumsumoftwononoverlappingsubarrays