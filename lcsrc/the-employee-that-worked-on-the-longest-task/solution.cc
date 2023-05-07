#include "solution.h"

#include <algorithm>
#include <ranges>
#include <span>
#include <vector>
#include <xutility>

#include "lcsrc/lib/io_helper.h"

namespace leetcode::theemployeethatworkedonthelongesttask {

int Solve(int /**/, const std::vector<std::vector<int>>& logs) {
  const std::vector<std::vector<int>> tmp{{0, 0}};
  const auto s = std::vector{
      std::span<const std::vector<int>>{tmp},
      std::span<const std::vector<int>>{logs},
  };
  return -std::ranges::max(
              std::ranges::views::zip(logs, s | std::ranges::views::join)  //
              | std::ranges::views::transform([](const auto& i) {
                  return std::pair{std::get<0>(i)[1] - std::get<1>(i)[1], -std::get<0>(i)[0]};
                }))
              .second;
}

namespace standard {
int Solve(int /**/, const std::vector<std::vector<int>>& logs) {
  int cur = 0;
  return -std::ranges::max(
              logs  //
              | std::ranges::views::transform([&cur](const auto& l) {
                  auto res = std::pair{l[1] - cur, -l[0]};
                  cur = l[1];
                  return res;
                }))
              .second;
  const auto times = logs  //
                     | std::ranges::views::transform([&cur](const auto& l) {
                         auto res = std::pair{l[1] - cur, -l[0]};
                         cur = l[1];
                         return res;
                       })  //
                     | std::ranges::to<std::vector<std::pair<int, int>>>();
  return -std::ranges::max_element(times)->second;
}

int Solve1(int /**/, const std::vector<std::vector<int>>& logs) {
  std::vector<std::pair<int, int>> times(logs.size());
  int cur = 0;
  std::transform(logs.cbegin(), logs.cend(), times.begin(), [&cur](const auto& l) {
    auto res = std::pair{l[1] - cur, -l[0]};
    cur = l[1];
    return res;
  });
  return -std::max_element(times.cbegin(), times.cend())->second;
}
}  // namespace standard

}  // namespace leetcode::theemployeethatworkedonthelongesttask