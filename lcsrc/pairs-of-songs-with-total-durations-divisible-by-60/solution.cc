#include "solution.h"

#include <algorithm>
#include <ranges>
#include <xutility>

namespace leetcode::pairsofsongswithtotaldurationsdivisibleby60 {

int Solve(const std::vector<int>& time) {
  auto times = std::map<int, int>{};
  for (int i : time | std::ranges::views::transform([](const int i) { return i % 60; })) {
    times[i]++;
  }
  return std::ranges::fold_left(
      times                                                                     //
          | std::ranges::views::keys                                            //
          | std::ranges::views::take_while([](const int i) { return i > 30; })  //
          | std::ranges::views::transform([&times](const int k) {
              if (k == 30 || k == 0) {
                return times[k] * (times[k] - 1) / 2;
              }
              return times[k] * times[60 - k];
            }),
      0,
      std::plus<>());
}

namespace standard {
int Solve(const std::vector<int>& time) {
  auto times = std::map<int, int>{};
  for (const auto& i : time) {
    times[i % 60]++;
  }
  int res = 0;
  for (const auto [k, v] : times) {
    if (k > 30) {
      break;
    }
    if (k == 30 || k == 0) {
      res += v * (v - 1) / 2;
    } else {
      res += v * times[60 - k];
    }
  }
  return res;
}

}  // namespace standard

}  // namespace leetcode::pairsofsongswithtotaldurationsdivisibleby60