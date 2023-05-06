#include "solution.h"

#include <iterator>
#include <utility>
#include <vector>

#include "lcsrc/lib/io_helper.h"

using namespace leetcode::lib;

namespace leetcode::minimumnumberoffrogscroaking {

template <class First, class... Args>
bool Equal(First&& f, Args&&... args) {
  return ((f == args) && ...);
}

int Solve(const std::string& croakOfFrogs) {
  // TODO(): your solution here
  return {};
}

namespace standard {
int Solve(const std::string& croakOfFrogs) {
  auto index = std::map<char, int>{
      {'c', 0},
      {'r', 1},
      {'o', 2},
      {'a', 3},
      {'k', 4},
  };
  std::vector<std::vector<int>> croaks(5);
  for (int i = 0; i < croakOfFrogs.size(); ++i) {
    croaks[index[croakOfFrogs[i]]].emplace_back(i);
  }
  std::cout << croaks << "\n";

  if (!Equal(
          croaks[0].size(),
          croaks[1].size(),
          croaks[2].size(),
          croaks[3].size(),
          croaks[4].size())) {
    return -1;
  }

  int res = 0;
  std::set<int> ps;
  const auto pop = [&ps]() {
    auto end = ps.end();
    ps.erase(std::prev(end));
  };
  for (int j = static_cast<int>(croaks[0].size()) - 1; j >= 0; --j) {
    int cur = -1;
    for (const auto& i : croaks) {
      if (i[j] <= cur) {
        return -1;
      }
      cur = i[j];
    }

    while (!ps.empty() && cur < *ps.rbegin()) {
      pop();
    }
    ps.emplace(croaks[0][j]);
    res = std::max(res, static_cast<int>(ps.size()));
  }

  return res;
}
}  // namespace standard

}  // namespace leetcode::minimumnumberoffrogscroaking