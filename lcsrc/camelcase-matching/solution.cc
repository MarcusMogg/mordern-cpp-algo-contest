#include "solution.h"

#include <algorithm>
#include <cctype>
#include <ranges>
#include <string_view>
#include <vector>

namespace leetcode::camelcasematching {

using namespace std::ranges;
using namespace leetcode::lib;

bool CheckMatch(std::string_view q, std::string_view pattern) {
  for (const char c : pattern) {
    while (!q.empty() && *q.begin() != c) {
      if (islower(*q.begin()) == 0) {
        return false;
      }
      q = q.substr(1);
    }
    if (q.empty()) {
      return false;
    }
    q = q.substr(1);
  }
  return std::ranges::all_of(q, [](char c) { return islower(c) != 0; });
}

std::vector<bool> Solve(const std::vector<std::string>& queries, const std::string& pattern) {
  return queries                                                                                  //
         | views::transform([&pattern](const std::string& q) { return CheckMatch(q, pattern); })  //
         | to<std::vector<bool>>();
}

namespace standard {

bool CheckMatch(std::string_view q, std::string_view pattern) {
  for (const char c : pattern) {
    while (!q.empty() && *q.begin() != c) {
      if (islower(*q.begin()) == 0) {
        return false;
      }
      q = q.substr(1);
    }
    if (q.empty()) {
      return false;
    }
    q = q.substr(1);
  }
  return std::all_of(q.begin(), q.end(), [](char c) { return islower(c) != 0; });
}
std::vector<bool> Solve(const std::vector<std::string>& queries, const std::string& pattern) {
  auto res = std::vector<bool>();
  for (const auto& i : queries) {
    res.emplace_back(CheckMatch(i, pattern));
  }
  return res;
}
}  // namespace standard
}  // namespace leetcode::camelcasematching