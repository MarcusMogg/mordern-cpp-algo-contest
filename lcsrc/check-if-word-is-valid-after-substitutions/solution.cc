#include "solution.h"

#include <stack>

namespace leetcode::checkifwordisvalidaftersubstitutions {

bool Solve(const std::string& s) {
  // TODO(): your solution here
  return {};
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