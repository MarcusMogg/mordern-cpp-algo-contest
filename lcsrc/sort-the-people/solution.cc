#include "solution.h"

#include <vcruntime.h>

#include <algorithm>
#include <iterator>
#include <ranges>
#include <string_view>

namespace leetcode::sortthepeople {

using namespace std::ranges;
using namespace leetcode::lib;

std::vector<std::string> Solve(
    const std::vector<std::string>& names, const std::vector<int>& heights) {
  auto height_index = views::iota(0U, heights.size()) | to<std::vector<size_t>>();
  std::ranges::sort(
      height_index, std::ranges::greater{}, [&heights](const size_t i) { return heights[i]; });

  return height_index                                                       //
         | views::transform([&names](const size_t i) { return names[i]; })  //
         | to<std::vector<std::string>>();                                  //
}

namespace standard {
std::vector<std::string> Solve(
    const std::vector<std::string>& names, const std::vector<int>& heights) {
  auto m = std::map<int, int>{};
  for (int i = 0; i < names.size(); ++i) {
    m[heights[i]] = i;
  }
  std::vector<std::string> res(names.size());
  std::transform(
      m.crbegin(), m.crend(), res.begin(), [&](const auto& i) { return names[i.second]; });
  return res;
}
}  // namespace standard

}  // namespace leetcode::sortthepeople