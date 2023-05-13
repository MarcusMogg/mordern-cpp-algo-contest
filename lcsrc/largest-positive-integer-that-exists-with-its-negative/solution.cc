#include "solution.h"

#include <algorithm>

namespace leetcode::largestpositiveintegerthatexistswithitsnegative {

int Solve(const std::vector<int>& nums) {
  // TODO(): your solution here
  return {};
}

namespace standard {
int Solve(const std::vector<int>& data) {
  auto nums = data;
  std::sort(nums.begin(), nums.end());
  int l = 0;
  int r = static_cast<int>(nums.size()) - 1;
  for (; l < r; l++) {
    for (; l < r && nums[l] + nums[r] > 0; r--) {
    }
    if (nums[l] + nums[r] == 0) {
      return nums[r];
    }
  }
  return -1;
}
}  // namespace standard

}  // namespace leetcode::largestpositiveintegerthatexistswithitsnegative