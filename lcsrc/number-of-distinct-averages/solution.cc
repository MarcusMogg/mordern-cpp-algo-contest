#include "solution.h"

#include <algorithm>
#include <unordered_set>

namespace leetcode::numberofdistinctaverages {

int Solve(const std::vector<int>& nums) {
  // TODO(): your solution here
  return {};
}

namespace standard {
int Solve(const std::vector<int>& nums) {
  auto copy = nums;
  std::sort(copy.begin(), copy.end());
  auto res = std::unordered_set<int>{};

  for (auto begin = copy.begin(), end = copy.rbegin().base() - 1; begin < end; ++begin, --end) {
    res.insert(*begin + *end);
  }

  return static_cast<int>(res.size());
}
}  // namespace standard

}  // namespace leetcode::numberofdistinctaverages