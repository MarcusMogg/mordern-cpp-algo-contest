#include "solution.h"

#include <algorithm>
#include <vector>

namespace leetcode::oddstringdifference {

std::string Solve(const std::vector<std::string>& words) {
  // TODO(): your solution here
  return {};
}

namespace standard {
std::string Solve(const std::vector<std::string>& words) {
  std::vector<std::vector<int>> diff(words.size());
  std::transform(words.begin(), words.end(), diff.begin(), [](const auto& s) {
    std::vector<int> tmp(s.size(), 0);
    std::transform(
        s.begin() + 1, s.end(), s.begin(), tmp.begin(), [](const auto& c1, const auto& c2) {
          return static_cast<int>(c1) - static_cast<int>(c2);
        });
    return tmp;
  });
  for (int i = 1; i + 1 < diff.size(); ++i) {
    if (diff[i] != diff[i - 1] && diff[i] != diff[i + 1]) {
      return words[i];
    }
  }
  if (diff[0] != diff[1]) {
    return words[0];
  }
  return words.back();
}
}  // namespace standard

}  // namespace leetcode::oddstringdifference