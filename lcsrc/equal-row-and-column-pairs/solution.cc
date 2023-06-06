#include "solution.h"

#include <set>
#include <unordered_set>
#include <utility>
#include <vector>

namespace leetcode::equalrowandcolumnpairs {

int Solve(const std::vector<std::vector<int>>& grid) {
  // TODO(): your solution here
  return {};
}

namespace standard {
int Solve(const std::vector<std::vector<int>>& grid) {
  auto cnt = std::multiset<std::vector<int>>{};
  for (int i = 0; i < grid[0].size(); i++) {
    std::vector<int> tmp;
    tmp.reserve(grid.size());
    for (const auto& j : grid) {
      tmp.emplace_back(j[i]);
    }
    cnt.emplace(std::move(tmp));
  }
  int res = 0;
  for (const auto& i : grid) {
    res += static_cast<int>(cnt.count(i));
  }
  return res;
}
}  // namespace standard

}  // namespace leetcode::equalrowandcolumnpairs