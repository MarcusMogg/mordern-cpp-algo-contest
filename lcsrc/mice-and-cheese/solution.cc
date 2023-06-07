#include "solution.h"

#include <queue>

namespace leetcode::miceandcheese {

int Solve(const std::vector<int>& reward1, const std::vector<int>& reward2, int k) {
  // TODO(): your solution here
  return {};
}

namespace standard {
int Solve(const std::vector<int>& reward1, const std::vector<int>& reward2, int k) {
  auto q = std::priority_queue<int>{};
  int res = 0;
  for (int i = 0; i < reward1.size(); i++) {
    res += reward2[i];
    q.emplace(reward2[i] - reward1[i]);
    if (q.size() > k) {
      q.pop();
    }
  }
  while (!q.empty()) {
    res -= q.top();
    q.pop();
  }
  return res;
}
}  // namespace standard

}  // namespace leetcode::miceandcheese