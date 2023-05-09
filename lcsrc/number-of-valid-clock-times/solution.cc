#include "solution.h"

#include <algorithm>
#include <format>
#include <ranges>
#include <string>
#include <string_view>

namespace leetcode::numberofvalidclocktimes {

bool Same(std::string_view l, std::string_view r) {
  const auto [lrng, rrng] =
      std::ranges::mismatch(l, r, [](char l, char r) { return l == r || (l == '?' || r == '?'); });
  return lrng == l.end() && rrng == r.end();
}

int Solve(const std::string& time) {
  std::string_view hour{time.begin(), time.begin() + 2};
  std::string_view minute{time.begin() + 3, time.end()};

  const auto h = std::ranges::count(std::ranges::views::iota(0, 24), true, [&hour](int i) {
    return Same(hour, std::format("{:0>2}", i));
  });
  const auto m = std::ranges::count(std::ranges::views::iota(0, 60), true, [&minute](int i) {
    return Same(minute, std::format("{:0>2}", i));
  });

  return static_cast<int>(h * m);
}

namespace standard {
bool Same(std::string_view l, std::string_view r) {
  if (l.size() != r.size()) {
    return false;
  }
  return std::mismatch(l.begin(), l.end(), r.begin(), r.end(), [](char l, char r) {
           return l == r || (l == '?' || r == '?');
         }).first == l.end();
}
std::string ToStr(int i) {
  std::string res = std::to_string(i);
  while (res.size() < 2) {
    res.insert(res.begin(), '0');
  }
  return res;
}
int Solve(const std::string& time) {
  std::string_view hour{time.begin(), time.begin() + 2};
  std::string_view minute{time.begin() + 3, time.end()};

  int h = 0;
  int m = 0;

  for (int i = 0; i < 24; i++) {
    if (Same(hour, ToStr(i))) {
      ++h;
    }
  }
  for (int i = 0; i < 60; i++) {
    if (Same(minute, ToStr(i))) {
      ++m;
    }
  }
  return h * m;
}
}  // namespace standard

}  // namespace leetcode::numberofvalidclocktimes