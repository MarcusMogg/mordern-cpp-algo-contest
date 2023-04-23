#include "solution.h"

#include <algorithm>
#include <limits>
#include <ranges>

namespace leetcode::fillingbookcaseshelves {

using namespace std::ranges;

int Solve(const std::vector<std::vector<int>>& books, int shelfWidth) {
  auto dp = std::vector(books.size() + 1, std::numeric_limits<int>::max());
  dp[0] = 0;

  for (int i : views::iota(0, static_cast<int>(books.size()))) {
    int cur_width = 0;
    int max_height = 0;
    int& cur_dp = dp[i + 1];
    for (int j : views::iota(0, i + 1) | views::reverse) {
      cur_width += books[j][0];
      if (cur_width > shelfWidth) {
        break;
      }
      max_height = std::max(max_height, books[j][1]);
      cur_dp = std::min(cur_dp, dp[j] + max_height);
    }
  }
  return dp.back();
}

namespace standard {
int Solve(const std::vector<std::vector<int>>& books, int shelfWidth) {
  auto dp = std::vector(books.size() + 1, std::numeric_limits<int>::max());
  dp[0] = 0;

  for (int i = 0; i < books.size(); ++i) {
    int cur_width = 0;
    int max_height = 0;
    int& cur_dp = dp[i + 1];
    for (int j = i; j >= 0; --j) {
      cur_width += books[j][0];
      if (cur_width > shelfWidth) {
        break;
      }
      max_height = std::max(max_height, books[j][1]);
      cur_dp = std::min(cur_dp, dp[j] + max_height);
    }
  }
  return dp.back();
}
}  // namespace standard

}  // namespace leetcode::fillingbookcaseshelves