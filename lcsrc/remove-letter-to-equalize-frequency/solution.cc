#include "solution.h"

#include <algorithm>
#include <functional>
#include <ranges>

namespace leetcode::removelettertoequalizefrequency {

bool Solve(const std::string& word) {
  auto cnt = std::vector<int>(26);
  for (const auto& i : word) {
    cnt[i - 'a']++;
  }
  const auto not_zero = [](int cur) { return cur != 0; };

  for (auto& i : cnt | std::ranges::views::filter(not_zero)) {
    --i;
    const int target = *std::ranges::find_if(cnt, not_zero);
    if (std::ranges::all_of(cnt, [target](int cur) { return cur == 0 || cur == target; })) {
      return true;
    }
    ++i;
  }
  return {};
}

namespace standard {
bool Solve(const std::string& word) {
  auto cnt = std::vector<int>(26);
  for (const auto& i : word) {
    cnt[i - 'a']++;
  }
  for (auto& i : cnt) {
    if (i == 0) {
      continue;
    }
    --i;
    const int target = *std::find_if(cnt.cbegin(), cnt.cend(), [](int cur) { return cur != 0; });
    if (std::all_of(
            cnt.cbegin(), cnt.cend(), [target](int cur) { return cur == 0 || cur == target; })) {
      return true;
    }
    ++i;
  }
  return {};
}
// 为什么想不开
bool Solve1(const std::string& word) {
  auto cnt = std::vector<int>(26);
  for (const auto& i : word) {
    cnt[i - 'a']++;
  }
  auto number_cnt = std::map<int, int>{};
  for (const auto& i : cnt) {
    if (i != 0) {
      number_cnt[i]++;
    }
  }
  if (number_cnt.size() > 2) {
    return false;
  }
  if (number_cnt.size() == 1) {
    return number_cnt.begin()->first == 1 || number_cnt.begin()->second == 1;
  }
  if (number_cnt.rbegin()->second == 1) {
    if (number_cnt.rbegin()->first == 1 ||
        number_cnt.rbegin()->first - 1 == number_cnt.begin()->first) {
      return true;
    }
  }
  if (number_cnt.begin()->second == 1) {
    return number_cnt.begin()->first == 1 ||
           number_cnt.begin()->first - 1 == number_cnt.rbegin()->first;
  }
  return false;
}
}  // namespace standard

}  // namespace leetcode::removelettertoequalizefrequency