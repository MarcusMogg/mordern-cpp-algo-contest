#include "solution.h"

#include <algorithm>
#include <iterator>
#include <string_view>

namespace leetcode::sortthepeople {

std::vector<std::string> Solve(
    const std::vector<std::string>& names, const std::vector<int>& heights) {
  // TODO(): your solution here
  return {};
}

namespace standard {
std::vector<std::string> Solve(
    const std::vector<std::string>& names, const std::vector<int>& heights) {
  auto m = std::map<int, int>{};
  for (int i = 0; i < names.size(); ++i) {
    m[heights[i]] = i;
  }
  std::vector<std::string> res;
  res.reserve(names.size());
  std::transform(m.rbegin(), m.rend(), std::back_inserter(res), [&](const auto& i) {
    return names[i.second];
  });
  return res;
}
}  // namespace standard

}  // namespace leetcode::sortthepeople