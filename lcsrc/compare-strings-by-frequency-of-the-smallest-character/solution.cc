#include "solution.h"

#include <algorithm>
#include <limits>
#include <vector>

#include "lcsrc/lib/io_helper.h"
using namespace leetcode::lib;
namespace leetcode::comparestringsbyfrequencyofthesmallestcharacter {

std::vector<int> Solve(
    const std::vector<std::string>& queries, const std::vector<std::string>& words) {
  // TODO(): your solution here
  return {};
}

namespace standard {

int Frequency(std::string_view s) {
  int res = 0;
  char cur = std::numeric_limits<char>::max();
  for (const auto i : s) {
    if (i < cur) {
      res = 1;
      cur = i;
    } else if (i == cur) {
      res++;
    }
  }
  return res;
}

std::vector<int> Solve(
    const std::vector<std::string>& queries, const std::vector<std::string>& words) {
  std::vector<int> cnt(words.size(), 0);
  std::transform(words.begin(), words.end(), cnt.begin(), Frequency);
  std::sort(cnt.begin(), cnt.end());
  std::cout << cnt;
  std::vector<int> res;
  res.reserve(queries.size());
  for (const auto& i : queries) {
    auto f = Frequency(i);
    res.emplace_back(static_cast<int>(cnt.cend() - std::upper_bound(cnt.cbegin(), cnt.cend(), f)));
  }
  return res;
}
}  // namespace standard

}  // namespace leetcode::comparestringsbyfrequencyofthesmallestcharacter