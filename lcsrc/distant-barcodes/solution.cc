#include "solution.h"

#include <algorithm>
#include <functional>
#include <vector>

namespace leetcode::distantbarcodes {

std::vector<int> Solve(const std::vector<int>& barcodes) {
  // TODO(): your solution here
  return {};
}

namespace standard {
std::vector<int> Solve(const std::vector<int>& barcodes) {
  auto copy = barcodes;
  auto tmp = std::vector<std::pair<int, int>>(10001);
  for (int i = 0; i < tmp.size(); ++i) {
    tmp[i] = {0, i};
  }
  for (const auto& i : copy) {
    tmp[i].first++;
  }
  std::sort(tmp.begin(), tmp.end(), std::greater<>());
  int cur = 0;
  for (const auto& i : tmp) {
    for (int j = 0; j < i.first; j++) {
      copy[cur++] = i.second;
    }
  }

  int mid = (static_cast<int>(copy.size()) + 1) / 2;
  auto res = std::vector<int>();
  for (int i = 0; i < mid; i++) {
    res.emplace_back(copy[i]);
    if (mid + i < copy.size()) {
      res.emplace_back(copy[mid + i]);
    }
  }
  return res;
}
}  // namespace standard

}  // namespace leetcode::distantbarcodes