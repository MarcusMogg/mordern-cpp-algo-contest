#include "solution.h"

#include <algorithm>
#include <iterator>
#include <ranges>
#include <vector>

namespace leetcode::countvowelstringsinranges {
template <class T, class... Args>
bool In(T&& target, Args&&... args) {
  return ((target == args) || ...);
}

std::vector<int> Solve(
    const std::vector<std::string>& words, const std::vector<std::vector<int>>& queries) {
  using namespace std::ranges::views;
  auto cnt = std::vector<int>{0};
  for (auto&& i :
       words | transform([](const auto& s) {
         return static_cast<int>(
             In(s.front(), 'a', 'e', 'i', 'o', 'u') && In(s.back(), 'a', 'e', 'i', 'o', 'u'));
       })) {
    cnt.emplace_back(cnt.back() + i);
  }
  return queries                                                                   //
         | transform([&cnt](const auto& s) { return cnt[s[1] + 1] - cnt[s[0]]; })  //
         | std::ranges::to<std::vector<int>>();
}

namespace standard {

std::vector<int> Solve(
    const std::vector<std::string>& words, const std::vector<std::vector<int>>& queries) {
  std::vector<int> cnt(words.size() + 1, 0);
  std::transform(words.begin(), words.end(), cnt.begin() + 1, [](const auto& s) {
    return static_cast<int>(
        In(s.front(), 'a', 'e', 'i', 'o', 'u') && In(s.back(), 'a', 'e', 'i', 'o', 'u'));
  });
  for (int i = 1; i < cnt.size(); ++i) {
    cnt[i] = cnt[i - 1] + cnt[i];
  }
  std::vector<int> res(queries.size(), 0);
  std::transform(queries.begin(), queries.end(), res.begin(), [&cnt](const auto& s) {
    return cnt[s[1] + 1] - cnt[s[0]];
  });
  return res;
}
}  // namespace standard

}  // namespace leetcode::countvowelstringsinranges