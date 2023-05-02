#include "solution.h"

#include <queue>
#include <utility>
#include <vector>
#include <xutility>

namespace leetcode::timeneededtoinformallemployees {

int Solve(int n, int headID, const std::vector<int>& manager, const std::vector<int>& informTime) {
  auto children = std::vector<std::vector<int>>(n, std::vector<int>());
  for (int i = 0; i < manager.size(); ++i) {
    if (manager[i] == -1) {
      continue;
    }
    children[manager[i]].emplace_back(i);
  }
  // better in c++ 23 : Deducing This
  // const auto dfs = [&children, &informTime](this auto& self, int head, int ts) -> int {}
  // so we can use dfs(headID, 0) instead of dfs(dfs, headID, 0) both inside and outside lambda
  const auto dfs = [&children, &informTime](auto&& self, int head, int ts) -> int {
    ts = ts + informTime[head];
    int res = ts;
    for (const auto c : children[head]) {
      res = std::max(res, self(self, c, ts));
    }
    return res;
  };
  return dfs(dfs, headID, 0);
}

namespace standard {
int Solve(int n, int headID, const std::vector<int>& manager, const std::vector<int>& informTime) {
  auto children = std::vector<std::vector<int>>(n, std::vector<int>());
  for (int i = 0; i < manager.size(); ++i) {
    if (manager[i] == -1) {
      continue;
    }
    children[manager[i]].emplace_back(i);
  }
  auto q = std::queue<std::pair<int, int>>{};
  int res = 0;
  q.emplace(headID, 0);
  while (!q.empty()) {
    const auto [head, ts] = q.front();
    q.pop();
    if (!children[head].empty()) {
      for (const auto c : children[head]) {
        q.emplace(c, ts + informTime[head]);
      }
    }

    res = std::max(res, ts + informTime[head]);
  }
  return res;
}
}  // namespace standard

}  // namespace leetcode::timeneededtoinformallemployees