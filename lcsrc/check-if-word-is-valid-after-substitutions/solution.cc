#include "solution.h"

#include <stack>
#include <tuple>

namespace leetcode::checkifwordisvalidaftersubstitutions {

bool Solve(const std::string& s) {
  auto st = std::stack<char>{};
  const auto check_top = [&st](char c) { return !st.empty() && st.top() == c; };
  for (auto c : s) {
    if (c == 'a' || c == 'b') {
      st.push(c);
    } else if (c == 'c') {
      if (!check_top('b')) {
        return false;
      }
      st.pop();
      if (!check_top('a')) {
        return false;
      }
      st.pop();
    }
  }
  return st.empty();
}

namespace standard {
bool Solve(const std::string& s) {
  auto st = std::stack<char>{};
  for (auto c : s) {
    if (c == 'a' || c == 'b') {
      st.push(c);
    } else if (c == 'c') {
      if (st.empty() || st.top() != 'b') {
        return false;
      }
      st.pop();
      if (st.empty() || st.top() != 'a') {
        return false;
      }
      st.pop();
    }
  }
  return st.empty();
}
}  // namespace standard

}  // namespace leetcode::checkifwordisvalidaftersubstitutions