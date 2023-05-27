#include "solution.h"

#include <algorithm>
#include <limits>
#include <map>

namespace leetcode::statisticsfromalargesample {

std::vector<double> Solve(const std::vector<int>& count) {
  // TODO(): your solution here
  return {};
}

namespace standard {
std::vector<double> Solve(const std::vector<int>& count) {
  int minimum = std::numeric_limits<int>::max();
  int maxmum = std::numeric_limits<int>::min();
  double sum = 0;
  int cnt = 0;
  for (int i = 0; i < count.size(); ++i) {
    if (count[i] != 0) {
      minimum = std::min(minimum, i);
      maxmum = std::max(maxmum, i);
    }
    sum += 1.0 * i * count[i];
    cnt += count[i];
  }
  double mean = 0;
  int cnt2 = 0;
  for (int i = 0; i < count.size(); ++i) {
    cnt2 += count[i];
    if (cnt % 2 == 1 && cnt2 >= cnt / 2 + 1) {
      mean = i;
      break;
    }
    if (cnt % 2 == 0) {
      if (cnt2 - count[i] < cnt / 2 && cnt2 >= cnt / 2 + 1) {
        mean = i;
        break;
      }
      if (cnt2 == cnt / 2 && mean == 0) {
        mean += i;
      }
      if (cnt2 >= cnt / 2 + 1) {
        mean += i;
        mean /= 2;
        break;
      }
    }
  }
  return {
      static_cast<double>(minimum),
      static_cast<double>(maxmum),
      sum * 1.0 / cnt,
      mean,
      static_cast<double>(std::max_element(count.begin(), count.end()) - count.begin()),
  };
}
}  // namespace standard

}  // namespace leetcode::statisticsfromalargesample