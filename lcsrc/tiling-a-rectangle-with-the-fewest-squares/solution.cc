#include "solution.h"

#include <algorithm>

namespace leetcode::tilingarectanglewiththefewestsquares {

int Solve(int n, int m) {
  // TODO(): your solution here
  return {};
}

namespace standard {
int Solve(int n, int m) {
  auto [min, max] = std::pair(std::min(n, m), std::max(n, m));

  int res = max / min;
  if (res * min == max) {
    return res;
  }
  return res + Solve(min, max - res * min);
}
}  // namespace standard

}  // namespace leetcode::tilingarectanglewiththefewestsquares