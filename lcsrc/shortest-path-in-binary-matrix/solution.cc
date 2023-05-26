#include "solution.h"

#include <array>
#include <queue>
#include <tuple>

namespace leetcode::shortestpathinbinarymatrix {

int Solve(const std::vector<std::vector<int>>& grid) {
  // TODO(): your solution here
  return {};
}

namespace standard {

static constexpr std::array kDir = {
    std::pair{-1, 0},
    std::pair{0, 1},
    std::pair{1, 0},
    std::pair{0, -1},
    std::pair{-1, -1},
    std::pair{-1, 1},
    std::pair{1, -1},
    std::pair{1, 1},
};

int Solve(const std::vector<std::vector<int>>& grid) {
  if (grid[0][0] != 0 || grid.back().back() != 0) {
    return -1;
  }
  if (grid.size() == 1 && grid[0].size() == 1) {
    return 1;
  }
  auto clone = grid;
  std::queue<std::tuple<int, int, int>> q;
  q.emplace(0, 0, 1);
  clone[0][0] = 1;
  const auto check = [&clone, &grid](int i, int j) {
    return i >= 0 && j >= 0 && i < grid.size() && j < grid[0].size() && clone[i][j] == 0;
  };
  while (!q.empty()) {
    const auto [curi, curj, cnt] = q.front();
    q.pop();
    for (const auto& [i, j] : kDir) {
      if (check(curi + i, curj + j)) {
        if (curi + i + 1 == grid.size() && curj + j + 1 == grid[0].size()) {
          return cnt + 1;
        }
        q.emplace(curi + i, curj + j, cnt + 1);
        clone[curi + i][curj + j] = 1;
      }
    }
  }

  return -1;
}
}  // namespace standard

}  // namespace leetcode::shortestpathinbinarymatrix