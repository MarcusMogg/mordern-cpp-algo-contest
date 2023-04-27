#include "solution.h"

#include <algorithm>
#include <map>
#include <ranges>
#include <string_view>
#include <vector>
#include <xutility>

using namespace std::ranges;
using namespace leetcode::lib;

namespace leetcode::longeststringchain {
bool IsPrev(std::string_view longer, std::string_view shorter) {
  int cnt = 0;
  for (char i : longer) {
    if (i == *shorter.begin()) {
      shorter = shorter.substr(1);
    } else {
      cnt++;
    }
    if (cnt > 1) {
      return false;
    }
  }
  return true;
}

int Solve(const std::vector<std::string>& words) {
  auto words_view =
      words                                                                                     //
      | views::transform([](const auto& i) { return std::pair<std::string_view, int>(i, 1); })  //
      | to<std::vector<std::pair<std::string_view, int>>>();

  int res = 1;

  for (subrange prev{words_view.begin(), words_view.begin()},
       remain{words_view.begin(), words_view.end()};
       int len : views::iota(1) | views::take_while([&remain](auto) { return !remain.empty(); })) {
    remain =
        std::ranges::partition(remain, [&len](const auto& sv) { return sv.first.size() < len; });
    subrange cur{prev.end(), remain.begin()};
    if (cur.empty()) {
      continue;
    }
    for (auto& i : cur) {
      for (const auto& j : prev) {
        if (IsPrev(i.first, j.first)) {
          i.second = std::max(i.second, j.second + 1);
        }
      }

      res = std::max(res, i.second);
    }
    prev = cur;
  }
  return res;
}

namespace standard {

int Solve(const std::vector<std::string>& words) {
  std::vector<std::string_view> words_view(words.begin(), words.end());
  std::vector<int> dp(words.size(), 1);
  int res = 1;

  for (int l = 0, r = 0, len = 1; r < words.size(); len++) {
    const auto it =
        std::partition(words_view.begin() + r, words_view.end(), [&len](const auto& sv) {
          return sv.size() < len;
        });
    if (it == words_view.begin() + r) {
      continue;
    }
    int mid = r;
    r = static_cast<int>(it - words_view.begin());

    for (int i = mid; i < r; ++i) {
      int cur = 1;
      for (int j = l; j < mid; ++j) {
        if (IsPrev(words_view[i], words_view[j])) {
          cur = std::max(cur, dp[j] + 1);
        }
      }
      dp[i] = cur;
      res = std::max(res, cur);
    }
    l = mid;
  }
  return res;
}
}  // namespace standard

}  // namespace leetcode::longeststringchain