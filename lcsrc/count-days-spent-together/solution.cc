#include "solution.h"

#include <algorithm>
#include <array>
#include <charconv>
#include <string>
#include <string_view>

namespace leetcode::countdaysspenttogether {

static constexpr auto kDays = std::array{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int ToInt(std::string_view sv) {
  int value;
  if (std::from_chars(sv.data(), sv.data() + sv.size(), value).ec == std::errc{}) {
    return value;
  }
  return 0;
}

int Solve(
    const std::string& arriveAlice,
    const std::string& leaveAlice,
    const std::string& arriveBob,
    const std::string& leaveBob) {
  std::string_view begin = std::max(arriveAlice, arriveBob);
  std::string_view end = std::min(leaveAlice, leaveBob);

  int begin_month = ToInt(begin.substr(0, 2));
  int begin_day = ToInt(begin.substr(3));
  int end_month = ToInt(end.substr(0, 2));
  int end_day = ToInt(end.substr(3));

  int res = 0;
  while (begin_month < end_month) {
    res += kDays[begin_month];
    begin_month++;
  }
  if (begin_month == end_month) {
    res -= begin_day - 1;
    res += end_day;
  }

  return std::max(0, res);
}

namespace standard {
int Solve(
    const std::string& arriveAlice,
    const std::string& leaveAlice,
    const std::string& arriveBob,
    const std::string& leaveBob) {
  std::string_view begin = std::max(arriveAlice, arriveBob);
  std::string_view end = std::min(leaveAlice, leaveBob);

  int begin_month = ToInt(begin.substr(0, 2));
  int begin_day = ToInt(begin.substr(3));
  int end_month = ToInt(end.substr(0, 2));
  int end_day = ToInt(end.substr(3));

  int res = 0;
  while (begin_month < end_month) {
    res += kDays[begin_month];
    begin_month++;
  }
  if (begin_month == end_month) {
    res -= begin_day - 1;
    res += end_day;
  }

  return std::max(0, res);
}
}  // namespace standard

}  // namespace leetcode::countdaysspenttogether