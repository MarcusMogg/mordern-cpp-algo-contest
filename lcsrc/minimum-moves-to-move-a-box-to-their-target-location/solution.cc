#include "solution.h"

#include <limits>
#include <map>
#include <queue>
#include <set>
#include <utility>
#include <vector>

#include "lcsrc/lib/io_helper.h"

using namespace leetcode::lib;

namespace leetcode::minimummovestomoveaboxtotheirtargetlocation {

int Solve(const std::vector<std::vector<char>>& grid) {
  // TODO(): your solution here
  return {};
}

namespace standard {

static constexpr int kIndex[] = {-1, 0, 1, 0};

template <class Target, class... Args>
bool In(Target t, Args... args) {
  return ((t == args) || ...);
}

bool Safe(const std::vector<std::vector<char>>& grid, int x, int y) {
  return x >= 0 && x < grid.size() && y >= 0 && y < grid[x].size();
}

bool Reachable(
    const std::vector<std::vector<char>>& grid,
    std::map<std::pair<int, int>, bool>& cache,
    std::pair<int, int> pos,
    std::pair<int, int> target) {
  if (pos == target) {
    return true;
  }
  if (cache[pos]) {
    return false;
  }
  // std::cout << "oo" << pos << "\n";

  cache[pos] = true;
  for (int i = 0; i < 4; ++i) {
    auto [x, y] = pos;
    x += kIndex[i];
    y += kIndex[3 - i];
    if (!Safe(grid, x, y) || !In(grid[x][y], '.')) {
      continue;
    }
    if (Reachable(grid, cache, {x, y}, target)) {
      return true;
    }
  }

  // cache[pos] = false;

  return false;
}

int Solve(const std::vector<std::vector<char>>& grid) {
  auto copy = grid;
  auto cache = std::map<std::pair<std::pair<int, int>, std::pair<int, int>>, bool>{};

  std::pair<int, int> pos_box;
  std::pair<int, int> pos_people;
  std::pair<int, int> pos_target;
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[i].size(); j++) {
      if (grid[i][j] == 'T') {
        pos_target = {i, j};
        copy[i][j] = '.';
      } else if (grid[i][j] == 'B') {
        pos_box = {i, j};
        copy[i][j] = '.';
      } else if (grid[i][j] == 'S') {
        pos_people = {i, j};
        copy[i][j] = '.';
      }
    }
  }

  std::queue<std::tuple<std::pair<int, int>, std::pair<int, int>, int>> q;

  q.emplace(pos_box, pos_people, 0);
  while (!q.empty()) {
    const auto [pos_box, pos_people, res] = q.front();
    // std::cout << pos_box << pos_people << "\n";
    q.pop();
    std::vector<int> tmp_pos;

    copy[pos_box.first][pos_box.second] = 'B';
    for (int i = 0; i < 4; ++i) {
      auto [x, y] = pos_box;
      x += kIndex[i];
      y += kIndex[3 - i];
      if (!Safe(copy, x, y) || !In(copy[x][y], '.')) {
        continue;
      }
      std::map<std::pair<int, int>, bool> cache1;
      if (!Reachable(copy, cache1, pos_people, {x, y})) {
        continue;
      }
      if (cache[{pos_box, {x, y}}]) {
        continue;
      }

      // std::cout << x << y << "\n";
      cache[{pos_box, {x, y}}] = true;
      tmp_pos.emplace_back(i);
    }
    for (int i : tmp_pos) {
      auto [x, y] = pos_box;
      x += kIndex[i];
      y += kIndex[3 - i];

      auto [nx, ny] = pos_box;
      nx -= kIndex[i];
      ny -= kIndex[3 - i];
      if (pos_target == std::pair{nx, ny}) {
        return res + 1;
      }
      //   std::cout << nx << ny << "\n";
      if (!Safe(copy, nx, ny) || !In(copy[nx][ny], '.')) {
        continue;
      }

      q.emplace(std::pair{nx, ny}, pos_box, res + 1);
    }
    copy[pos_box.first][pos_box.second] = '.';
  }

  return -1;
}
}  // namespace standard

}  // namespace leetcode::minimummovestomoveaboxtotheirtargetlocation