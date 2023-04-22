#include "solution.h"

#include <algorithm>
#include <vector>

#include "lcsrc/lib/io_helper.h"

using namespace leetcode::lib;

namespace leetcode::longestarithmeticsubsequence {

int Solve(const std::vector<int>& nums) {
  // TODO(): your solution here
  return {};
}

namespace standard {
int Solve(const std::vector<int>& nums) {
  const int max_diff =
      *std::max_element(nums.begin(), nums.end()) - *std::min_element(nums.begin(), nums.end());
  auto dp = std::vector(nums.size(), std::vector<int>(static_cast<size_t>(max_diff * 2 + 1), 1));
  int res = 0;
  for (int i = 0; i < nums.size(); i++) {
    for (int j = 0; j < i; j++) {
      const int diff = nums[i] - nums[j] + max_diff;
      dp[i][diff] = std::max(dp[i][diff], dp[j][diff] + 1);
      res = std::max(res, dp[i][diff]);
    }
  }

  return res;
}
}  // namespace standard

}  // namespace leetcode::longestarithmeticsubsequence