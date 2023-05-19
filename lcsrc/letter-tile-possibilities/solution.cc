#include "solution.h"

#include <algorithm>

namespace leetcode::lettertilepossibilities {

int Solve(const std::string& tiles) {
  // TODO(): your solution here
  return {};
}

namespace standard {

int Dfs(std::map<int, int>& cnt, int target) {
  if (target == 1) {
    return std::count_if(cnt.begin(), cnt.end(), [](const auto& p) { return p.second != 0; });
  }
  int res = 0;
  for (auto& [k, v] : cnt) {
    if (v > 0) {
      v--;
      res += Dfs(cnt, target - 1);
      v++;
    }
  }
  return res;
}

int Solve(const std::string& tiles) {
  auto cnt = std::map<int, int>{};
  for (const auto& c : tiles) {
    cnt[c]++;
  }
  int res = 0;
  for (int i = 0; i < tiles.size(); i++) {
    res += Dfs(cnt, i + 1);
  }
  return res;
}
}  // namespace standard

}  // namespace leetcode::lettertilepossibilities