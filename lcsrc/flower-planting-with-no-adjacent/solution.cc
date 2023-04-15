#include "solution.h"

#include <algorithm>
#include <functional>
#include <ranges>
#include <vector>

#include "lcsrc/lib/io_helper.h"

using namespace leetcode::lib;
using namespace std::ranges;
using namespace std::ranges::views;
namespace leetcode::flowerplantingwithnoadjacent {

int FindFirst(const std::vector<std::reference_wrapper<int>>& v) {
  return (iota(1, 5) | filter([&v](int cur) { return std::ranges::find(v, cur) == v.end(); }))
      .front();
}

std::vector<int> Solve(const int& n, const std::vector<std::vector<int>>& paths) {
  std::vector<int> res(n, 0);
  std::vector<std::vector<std::reference_wrapper<int>>> m(n);
  for (const auto& p : paths) {
    m[p.front() - 1].emplace_back(std::ref(res[p.back() - 1]));
    m[p.back() - 1].emplace_back(std::ref(res[p.front() - 1]));
  }
  std::ranges::transform(m, res.begin(), FindFirst);

  return res;
}

namespace standard {
int FindFirst(const std::vector<std::reference_wrapper<int>>& v) {
  for (int i = 1; i <= 4; ++i) {
    if (std::find(v.begin(), v.end(), i) == v.end()) {
      return i;
    }
  }
  return 0;
}
std::vector<int> Solve(const int& n, const std::vector<std::vector<int>>& paths) {
  std::vector<int> res(n, 0);
  std::vector<std::vector<std::reference_wrapper<int>>> m(n);
  for (const auto& p : paths) {
    m[p.front() - 1].emplace_back(std::ref(res[p.back() - 1]));
    m[p.back() - 1].emplace_back(std::ref(res[p.front() - 1]));
  }
  std::transform(m.begin(), m.end(), res.begin(), FindFirst);
  return res;
}
}  // namespace standard
}  // namespace leetcode::flowerplantingwithnoadjacent