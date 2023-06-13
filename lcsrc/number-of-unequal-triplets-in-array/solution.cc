#include "solution.h"

namespace leetcode::numberofunequaltripletsinarray {

int Solve(const std::vector<int>& nums) {
  // TODO(): your solution here
  return {};
}

namespace standard {
int Solve(const std::vector<int>& nums) {
  int res = 0;
  for (int i = 0; i < nums.size(); ++i) {
    for (int j = i + 1; j < nums.size(); ++j) {
      if (nums[j] == nums[i]) {
        continue;
      }
      for (int k = j + 1; k < nums.size(); ++k) {
        if (nums[j] == nums[k] || nums[i] == nums[k]) {
          continue;
        }
        res++;
      }
    }
  }
  return res;
}
}  // namespace standard

}  // namespace leetcode::numberofunequaltripletsinarray
