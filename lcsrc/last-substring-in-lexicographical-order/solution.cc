#include "solution.h"

#include <algorithm>
#include <string_view>
#include <vector>

namespace leetcode::lastsubstringinlexicographicalorder {

std::string Solve(const std::string& s) {
  // TODO(): your solution here
  return {};
}

namespace standard {
std::string Solve(const std::string& s) {
  const auto c = *std::max_element(s.begin(), s.end());

  std::string_view res;

  for (int i = 0; i < s.size(); ++i) {
    if (s[i] != c) {
      continue;
    }
    for (int j = i + 1; j <= s.size(); ++j) {
      if (j - i >= res.size()) {
        res = std::string_view(s.c_str() + i);
        break;
      }
      if (res[j - i - 1] > s[j - 1]) {
        break;
      }
      if (res[j - i - 1] < s[j - 1]) {
        std::string_view cur(s.c_str() + i, j - i);
        res = std::max(res, cur);
      }
    }
  }

  return std::string(res);
}
}  // namespace standard

}  // namespace leetcode::lastsubstringinlexicographicalorder