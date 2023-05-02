#include "solution.h"

#include <concepts>
#include <ranges>
#include <utility>
#include <vector>

namespace leetcode::powerfulintegers {

std::vector<int> Solve(int x, int y, int bound) {
  auto res = std::set<int>{};
  if (x == 1) {
    x = bound;
  }
  if (y == 1) {
    y = bound;
  }
  // how to achieve a SteppedIota?
  // for (int i : SteppedIota(1, bound, [x](int cur) { return cur * x; })) {
  //   std::cout << i << "\n";
  //   for (int j : SteppedIota(1, bound, [y](int cur) { return cur * y; })) {
  //     if (i + j <= bound) {
  //       res.emplace(i + j);
  //     }
  //   }
  // }
  return {res.begin(), res.end()};
}

namespace standard {
std::vector<int> Solve(int x, int y, int bound) {
  auto res = std::set<int>{};
  if (x == 1) {
    x = bound;
  }
  if (y == 1) {
    y = bound;
  }
  for (int x_it = 1; x_it < bound; x_it *= x) {
    for (int y_it = 1; y_it < bound; y_it *= y) {
      if (x_it + y_it <= bound) {
        res.emplace(x_it + y_it);
      }
    }
  }
  return {res.begin(), res.end()};
}
}  // namespace standard

}  // namespace leetcode::powerfulintegers