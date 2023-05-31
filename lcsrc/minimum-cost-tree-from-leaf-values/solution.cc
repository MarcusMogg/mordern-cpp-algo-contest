#include "solution.h"

#include <algorithm>
#include <limits>
#include <map>
#include <numeric>
#include <tuple>
#include <vector>

namespace leetcode::minimumcosttreefromleafvalues {

int Solve(const std::vector<int>& arr) {
  // TODO(): your solution here
  return {};
}

namespace standard {
int Solve(const std::vector<int>& arr) {
  auto dp = std::vector<std::vector<std::pair<int, int>>>(
      arr.size(),
      std::vector(
          arr.size(),
          std::pair{
              std::numeric_limits<int>::min(),
              std::numeric_limits<int>::max(),
          }));
  for (int i = 0; i < arr.size(); ++i) {
    dp[i][i] = {arr[i], arr[i]};
  }
  for (int len = 2; len <= arr.size(); ++len) {
    for (int i = 0; i + len <= arr.size(); ++i) {
      int l = i;
      int r = l + len - 1;
      int min_res = std::numeric_limits<int>::max();
      for (int j = l; j + 1 <= r; ++j) {
        min_res = std::min(
            min_res, dp[l][j].first * dp[j + 1][r].first + dp[l][j].second + dp[j + 1][r].second);
      }
      dp[l][r] = {std::max(arr[l], dp[l + 1][r].first), min_res};
    }
  }

  return dp[0].back().second - std::accumulate(arr.begin(), arr.end(), 0);
}
}  // namespace standard

}  // namespace leetcode::minimumcosttreefromleafvalues