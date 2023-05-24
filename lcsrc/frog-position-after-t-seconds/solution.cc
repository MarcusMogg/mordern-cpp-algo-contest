#include "solution.h"

#include <map>
#include <tuple>
#include <vector>

#include "lcsrc/lib/io_helper.h"

using namespace leetcode::lib;

namespace leetcode::frogpositionaftertseconds {

double Solve(int n, const std::vector<std::vector<int>>& edges, int t, int target) {
  // TODO(): your solution here
  return {};
}

namespace standard {

void dfs(
    int parent,
    int cur,
    double probability,
    std::map<int, std::vector<int>>& tree,
    std::vector<bool>& visited,
    std::vector<std::tuple<int, double, bool>>& res) {
  visited[cur] = true;
  if (cur == 1) {
    res[cur] = {
        0,
        1,
        true,
    };
  } else {
    res[cur] = {
        std::get<0>(res[parent]) + 1,
        std::get<1>(res[parent]) * probability,
        true,
    };
  }
  double cnt = 0;
  for (const auto& child : tree[cur]) {
    if (visited[child]) {
      continue;
    }
    cnt++;
  }
  for (const auto& child : tree[cur]) {
    if (visited[child]) {
      continue;
    }
    std::get<2>(res[cur]) = false;
    dfs(cur, child, 1 / cnt, tree, visited, res);
  }
}
double Solve(int n, const std::vector<std::vector<int>>& edges, int t, int target) {
  auto tree = std::map<int, std::vector<int>>{};
  for (const auto& i : edges) {
    tree[i[0]].emplace_back(i[1]);
    tree[i[1]].emplace_back(i[0]);
  }
  // depth probability is_leaf
  auto res = std::vector<std::tuple<int, double, bool>>(n + 1);
  auto visited = std::vector<bool>(n + 1, false);
  dfs(-1, 1, 1, tree, visited, res);

  if (std::get<0>(res[target]) == t) {
    return std::get<1>(res[target]);
  }
  if (std::get<0>(res[target]) < t && std::get<2>(res[target])) {
    return std::get<1>(res[target]);
  }

  return 0;
}
}  // namespace standard

}  // namespace leetcode::frogpositionaftertseconds