#include "solution.h"

#include <numeric>
#include <ranges>
#include <utility>

namespace leetcode::averagevalueofevennumbersthataredivisiblebythree {

int Solve(const std::vector<int>& nums) {
  const auto res = std::ranges::fold_left(
      nums                                                                        //
          | std::ranges::views::filter([](const auto& i) { return i % 6 == 0; })  //
          | std::ranges::views::transform([](const auto& i) {
              return std::pair{i, 1};
            }),
      std::pair{0, 0},
      [](const auto& l, const auto& r) {
        return std::pair{l.first + r.first, l.second + r.second};
      });
  if (res.second == 0) {
    return 0;
  }
  return res.first / res.second;
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