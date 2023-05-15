#include "solution.h"

#include <bitset>
#include <map>
#include <unordered_map>

namespace leetcode::flipcolumnsformaximumnumberofequalrows {

int Solve(const std::vector<std::vector<int>>& matrix) {
  // TODO(): your solution here
  return {};
}

namespace standard {
int Solve(const std::vector<std::vector<int>>& matrix) {
  int res = 0;
  auto m = std::unordered_map<std::bitset<301>, int>{};
  for (const auto& i : matrix) {
    std::bitset<301> b;
    for (int j = 0; j < i.size(); j++) {
      if (i[j] == 1) {
        b.set(j);
      }
    }
    m[b]++;
  }
  for (const auto& [b, v] : m) {
    auto another = ~b;
    for (auto j = matrix[0].size(); j < another.size(); j++) {
      another.flip(j);
    }
    if (m.count(another) != 0) {
      res = std::max(v + m[another], res);
    } else {
      res = std::max(v, res);
    }
  }
  return res;
}
}  // namespace standard

}  // namespace leetcode::flipcolumnsformaximumnumberofequalrows