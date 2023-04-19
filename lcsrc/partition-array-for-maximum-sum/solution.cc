#include "solution.h"

#include <ranges>
#include <vector>

namespace leetcode::partitionarrayformaximumsum {
using namespace std::ranges;

int Solve(const std::vector<int>& arr, int k) {
  auto dp = std::vector<int>(arr.size() + 1, 0);
  for (int i : views::iota(0, static_cast<int>(arr.size()))) {
    int max_value = arr[i];
    for (int j : views::iota(0, std::min(k, i + 1))) {
      max_value = std::max(max_value, arr[i - j]);
      dp[i + 1] = std::max(dp[i + 1], dp[i - j] + max_value * (j + 1));
    }
  }
  return dp.back();
}

namespace standard {
int Solve(const std::vector<int>& arr, int k) {
  auto dp = std::vector<int>(arr.size() + 1, 0);
  for (int i = 0; i < arr.size(); ++i) {
    int max_value = arr[i];
    for (int j = 0; j < std::min(k, i + 1); ++j) {
      max_value = std::max(max_value, arr[i - j]);
      dp[i + 1] = std::max(dp[i + 1], dp[i - j] + max_value * (j + 1));
    }
  }
  return dp.back();
}
}  // namespace standard

}  // namespace leetcode::partitionarrayformaximumsum