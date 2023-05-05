#include "solution.h"

#include <algorithm>
#include <ranges>
#include <vector>
#include <xutility>

#include "lcsrc/lib/io_helper.h"

namespace leetcode::theemployeethatworkedonthelongesttask {

int Solve(int /**/, const std::vector<std::vector<int>>& logs) {
  return -std::max(
              std::ranges::max(
                  logs                           //
                  | std::ranges::views::take(1)  //
                  | std::ranges::views::transform([](const auto& l) {
                      return std::pair{l[1], -l[0]};
                    })),
              std::ranges::max(
                  std::ranges::views::zip(logs | std::ranges::views::drop(1), logs)  //
                  | std::ranges::views::transform([](const auto& i) {
                      return std::pair{std::get<0>(i)[1] - std::get<1>(i)[1], -std::get<0>(i)[0]};
                    })))
              .second;
}

namespace standard {
int Solve(int /**/, const std::vector<std::vector<int>>& logs) {
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