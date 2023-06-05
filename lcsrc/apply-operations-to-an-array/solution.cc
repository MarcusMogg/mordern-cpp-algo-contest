#include "solution.h"

#include <iterator>

namespace leetcode::applyoperationstoanarray {

std::vector<int> Solve(const std::vector<int>& nums) {
  // TODO(): your solution here
  return {};
}

namespace standard {
std::vector<int> Solve(const std::vector<int>& nums) {
  auto res = nums;
  for (int i = 0; i + 1 < res.size(); ++i) {
    if (res[i] == res[i + 1]) {
      res[i] = 2 * res[i];
      res[i + 1] = 0;
    }
  }
  for (int i = 0; i < res.size(); ++i) {
    bool v = true;
    for (int j = 0; j + i + 1 < res.size(); ++j) {
      if (res[j] == 0) {
        v = false;
        std::swap(res[j + 1], res[j]);
      }
    }
    if (v) {
      break;
    }
  }
  return res;
}
}  // namespace standard

}  // namespace leetcode::applyoperationstoanarray