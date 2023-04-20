#include "solution.h"

#include <algorithm>
#include <limits>
#include <utility>
#include <vector>

#include "lcsrc/lib/io_helper.h"

using namespace leetcode::lib;

namespace leetcode::makearraystrictlyincreasing {

int Solve(const std::vector<int>& arr1, const std::vector<int>& arr2) {
  // TODO(): your solution here
  return {};
}

namespace standard {
int Solve(const std::vector<int>& arr1, const std::vector<int>& arr2) {
  auto dp = std::vector(
      arr1.size() + 1, std::vector(arr1.size() + 1, std::numeric_limits<int>::max() - 1));

  dp[0][0] = -1;

  std::set<int> a2{arr2.begin(), arr2.end()};

  for (int i = 0; i < arr1.size(); ++i) {
    for (int j = 0; j <= i; ++j) {
      if (arr1[i] > dp[i][j]) {
        dp[i + 1][j] = std::min(dp[i + 1][j], arr1[i]);
      }
      const auto it0 = a2.upper_bound(dp[i][j]);
      if (it0 != a2.end()) {
        dp[i + 1][j + 1] = std::min(dp[i + 1][j + 1], *it0);
      }
    }
  }

  const auto res = std::find_if(dp.back().begin(), dp.back().end(), [](int i) {
    return i < std::numeric_limits<int>::max() - 1;
  });

  if (res == dp.back().end()) {
    return -1;
  }

  return static_cast<int>(res - dp.back().begin());
}
}  // namespace standard

}  // namespace leetcode::makearraystrictlyincreasing