#include "solution.h"

#include <utility>
#include <vector>

namespace leetcode::swapforlongestrepeatedcharactersubstring {

int Solve(const std::string& text) {
  // TODO(): your solution here
  return {};
}

namespace standard {
int Solve(const std::string& text) {
  int res = 0;

  auto ranges = std::vector<std::vector<std::pair<int, int>>>(26);

  int cur = 0;
  for (int i = 0; i < text.size(); ++i) {
    if (text[i] != text[cur]) {
      ranges[text[cur] - 'a'].emplace_back(cur, i);
      cur = i;
    }
  }
  ranges[text[cur] - 'a'].emplace_back(cur, static_cast<int>(text.size()));

  for (const auto& rngs : ranges) {
    if (rngs.empty()) {
      continue;
    }
    const int add = rngs.size() > 2 ? 1 : 0;
    for (int i = 1; i < rngs.size(); ++i) {
      if (rngs[i].first == rngs[i - 1].second + 1) {
        res = std::max(
            res, rngs[i].second - rngs[i].first + rngs[i - 1].second - rngs[i - 1].first + add);
      } else {
        res = std::max(res, rngs[i].second - rngs[i].first + 1);
      }
    }
    res = std::max(res, rngs[0].second - rngs[0].first + (rngs.size() > 1 ? 1 : 0));
  }

  return res;
}
}  // namespace standard

}  // namespace leetcode::swapforlongestrepeatedcharactersubstring