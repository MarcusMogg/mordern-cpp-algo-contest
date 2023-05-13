#include "solution.h"

#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

#include "lcsrc/lib/io_helper.h"

using namespace leetcode::lib;

namespace leetcode::smallestintegerdivisiblebyk {

int Solve(int k) {
  // TODO(): your solution here
  return {};
}

namespace standard {

int Solve(int k) {
  if (k % 2 == 0 || k % 5 == 0) {
    return -1;
  }
  int resid = 1 % k;
  int len = 1;
  while (resid != 0) {
    resid = (resid * 10 + 1) % k;
    len++;
  }
  return len;
}
}  // namespace standard

}  // namespace leetcode::smallestintegerdivisiblebyk