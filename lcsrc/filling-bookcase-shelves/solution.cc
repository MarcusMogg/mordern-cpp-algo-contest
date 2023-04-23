#include "solution.h"

#include <algorithm>
#include <limits>

namespace leetcode::fillingbookcaseshelves {

int Solve(const std::vector<std::vector<int>>& books, int shelfWidth) {
  // TODO(): your solution here
  return {};
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