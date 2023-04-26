#include "solution.h"

#include <iterator>
#include <type_traits>

namespace leetcode::maximumsumoftwononoverlappingsubarrays {

int Solve(const std::vector<int>& nums, int firstLen, int secondLen) {
  // TODO(): your solution here
  return {};
}

namespace standard {
int Solve(const std::vector<int>& nums, int firstLen, int secondLen) {
  const auto max_element_vec = []<class It>(It begin, It end) {
    auto max = *begin;
    std::vector<std::remove_cvref_t<decltype(*begin)>> res;
    std::transform(begin, end, std::back_inserter(res), [&max](const auto& cur) {
      max = std::max(cur, max);
      return max;
    });
    return res;
  };
  const auto first_max = max_element_vec(nums.cbegin(), nums.cend());
  int res = 0;
  int second_max = 0;
  for (int i = static_cast<int>(nums.size()) - 1; i >= firstLen; --i) {
    second_max = std::max(nums[i], second_max);
    if (i <= static_cast<int>(nums.size()) - secondLen) {
      res = std::max(res, first_max[i - 1] + second_max);
    }
  }
  second_max = 0;
  for (int i = static_cast<int>(nums.size()) - 1; i >= secondLen; --i) {
    second_max = std::max(nums[i], second_max);
    if (i <= static_cast<int>(nums.size()) - firstLen) {
      res = std::max(res, first_max[i - 1] + second_max);
    }
  }
  return res;
}
}  // namespace standard

}  // namespace leetcode::maximumsumoftwononoverlappingsubarrays