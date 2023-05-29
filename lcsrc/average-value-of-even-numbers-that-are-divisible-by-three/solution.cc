#include "solution.h"

#include <numeric>
#include <utility>

namespace leetcode::averagevalueofevennumbersthataredivisiblebythree {

int Solve(const std::vector<int>& nums) {
  // TODO(): your solution here
  return {};
}

namespace standard {
int Solve(const std::vector<int>& nums) {
  std::pair<int, int> res{0, 0};
  for (auto num : nums) {
    if (num % 6 == 0) {
      res.first += num;
      res.second += 1;
    }
  }
  if (res.second == 0) {
    return 0;
  }
  return res.first / res.second;
}
}  // namespace standard

}  // namespace leetcode::averagevalueofevennumbersthataredivisiblebythree