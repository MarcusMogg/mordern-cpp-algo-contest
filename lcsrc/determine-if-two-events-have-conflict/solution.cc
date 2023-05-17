#include "solution.h"

#include <string_view>

namespace leetcode::determineiftwoeventshaveconflict {

bool Solve(const std::vector<std::string>& event1, const std::vector<std::string>& event2) {
  // TODO(): your solution here
  return {};
}

namespace standard {
bool Solve(const std::vector<std::string>& event1, const std::vector<std::string>& event2) {
  auto max_start = std::max<std::string_view>(event1[0], event2[0]);
  auto min_end = std::min<std::string_view>(event1[1], event2[1]);
  return max_start <= min_end;
}
}  // namespace standard

}  // namespace leetcode::determineiftwoeventshaveconflict