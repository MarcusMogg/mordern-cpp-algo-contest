#include "solution.h"

#include <algorithm>
#include <limits>

namespace leetcode::maximumtastinessofcandybasket {

int Solve(const std::vector<int>& price, int k) {
  // TODO(): your solution here
  return {};
}

namespace standard {
int Solve(const std::vector<int>& price, int k) {
  auto copy = price;
  std::sort(copy.begin(), copy.end());

  int l = 0;
  int r = copy.back() - copy.front();
  int res = 0;

  const auto check = [&copy, &k](int diff) {
    int cnt = 0;
    int cur = std::numeric_limits<int>::min();
    for (int i : copy) {
      if (cur + diff <= i) {
        cnt++;
        cur = i;
      }
    }
    return cnt >= k;
  };

  while (l <= r) {
    int mid = (l + r) / 2;
    if (check(mid)) {
      l = mid + 1;
      res = mid;
    } else {
      r = mid - 1;
    }
  }

  return res;
}
}  // namespace standard

}  // namespace leetcode::maximumtastinessofcandybasket