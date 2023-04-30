#include "solution.h"

#include <vector>

namespace leetcode::movingstonesuntilconsecutive {

std::pair<int, int> GetDiff(int a, int b, int c) {
  std::vector v{a, b, c};
  std::sort(v.begin(), v.end());
  return {v[1] - v[0] - 1, v[2] - v[1] - 1};
}
std::pair<int, int> GetMinMax(int l, int r) {
  int min = 0;
  int max = l + r;
  if (r > 0) {
    min++;
    l = r - 1;
    r = 0;
  }
  if (l > 0) {
    min++;
  }

  return {min, max};
}

std::vector<int> Solve(int a, int b, int c) {
  // TODO(): your solution here
  return {};
}

namespace standard {

std::vector<int> Solve(int a, int b, int c) {
  const auto [l, r] = GetDiff(a, b, c);
  const auto [min1, max1] = GetMinMax(l, r);
  const auto [min2, max2] = GetMinMax(r, l);
  return {std::min(min1, min2), std::max(max1, max2)};
}
}  // namespace standard

}  // namespace leetcode::movingstonesuntilconsecutive