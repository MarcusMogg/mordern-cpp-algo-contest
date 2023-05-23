#include "solution.h"

#include <algorithm>
#include <functional>
#include <map>
#include <vector>

namespace leetcode::largestvaluesfromlabels {

int Solve(
    const std::vector<int>& values, const std::vector<int>& labels, int numWanted, int useLimit) {
  // TODO(): your solution here
  return {};
}

namespace standard {
int Solve(
    const std::vector<int>& values, const std::vector<int>& labels, int numWanted, int useLimit) {
  auto tmp = std::vector<std::pair<int, int>>(values.size());
  for (int i = 0; i < values.size(); ++i) {
    tmp[i] = {values[i], labels[i]};
  }
  std::sort(tmp.begin(), tmp.end(), std::greater<>());
  auto cnt = std::map<int, int>{};
  int res = 0;

  for (const auto& [v, k] : tmp) {
    if (cnt[k] >= useLimit) {
      continue;
    }
    cnt[k]++;
    res += v;
    --numWanted;
    if (numWanted <= 0) {
      break;
    }
  }

  return res;
}
}  // namespace standard

}  // namespace leetcode::largestvaluesfromlabels