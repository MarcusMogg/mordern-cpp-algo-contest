#include "solution.h"

#include <algorithm>
#include <vector>

namespace leetcode::maximumfruitsharvestedafteratmostksteps {

int Solve(const std::vector<std::vector<int>>& fruits, int startPos, int k) {
  // TODO(): your solution here
  return {};
}

namespace standard {
int Solve(const std::vector<std::vector<int>>& fruits, int startPos, int k) {
  auto sum = std::vector<int>(fruits.size() + 1, 0);
  for (int i = 0; i < fruits.size(); ++i) {
    sum[i + 1] = sum[i] + fruits[i][1];
  }
  const auto diffl = [&fruits, startPos](int l) {
    if (l < 0 || l >= fruits.size()) {
      return 0;
    }
    return std::max(0, startPos - fruits[l][0]);
  };
  const auto diffr = [&fruits, startPos](int l) {
    if (l < 0 || l >= fruits.size()) {
      return 0;
    }
    return std::max(0, fruits[l][0] - startPos);
  };
  int res = 0;
  int l = 0;
  int r = static_cast<int>(fruits.size()) - 1;
  int rbegin = r;
  while (rbegin >= 0 && fruits[rbegin][0] >= startPos) {
    --rbegin;
  }
  int lend = 0;
  while (lend < fruits.size() && fruits[lend][0] <= startPos) {
    ++lend;
  }
  r = rbegin + 1;
  // std::cout << lend << " " << rbegin << "\n";
  while (l < lend) {
    if (diffl(l) <= k) {
      res = std::max(res, sum[lend] - sum[l]);
    }
    while (r < fruits.size() && diffl(l) * 2 + diffr(r) <= k) {
      res = std::max(res, sum[r + 1] - sum[l]);
      r++;
    }
    l++;
  }
  l = lend - 1;
  r = static_cast<int>(fruits.size()) - 1;
  while (r > rbegin) {
    if (diffr(r) <= k) {
      res = std::max(res, sum[r + 1] - sum[rbegin + 1]);
    }
    while (l >= 0 && diffl(l) + diffr(r) * 2 <= k) {
      res = std::max(res, sum[r + 1] - sum[l]);
      l--;
    }
    r--;
  }
  return res;
}
}  // namespace standard

}  // namespace leetcode::maximumfruitsharvestedafteratmostksteps