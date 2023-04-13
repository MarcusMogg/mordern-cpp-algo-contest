#include "solution.h"

#include <map>
#include <xutility>

namespace leetcode::mostfrequentevenelement {
int Solve(const std::vector<int>& nums) {
  auto m = std::map<int, int>{};
  for (const auto& i : nums) {
    if (i % 2 == 0) {
      m[i]++;
    }
  }
  if (m.empty()) {
    m[-1] = 1;
  }

  const auto res = std::ranges::max_element(m, {}, [](const auto& it) { return it.second; });
  return res->first;
}

namespace standard {
int Solve(const std::vector<int>& /*unused*/) {
  // TODO(): official answer here
  return {};
}
}  // namespace standard
}  // namespace leetcode::mostfrequentevenelement