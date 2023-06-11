#include "solution.h"

#include <algorithm>
#include <map>
#include <vector>

#include "lcsrc/lib/leetcode_struct.h"

namespace leetcode::removezerosumconsecutivenodesfromlinkedlist {

ListNode* Solve(ListNode* head) {
  // TODO(): your solution here
  return {};
}

namespace standard {
ListNode* Solve(ListNode* head) {
  if (head == nullptr) {
    return nullptr;
  }
  auto cnt = std::vector<std::pair<int, ListNode*>>{
      {0, nullptr},
  };  // sum and parent node
  auto* cur = head;
  int cur_sum = 0;
  while (cur != nullptr) {
    cur_sum += cur->val;
    std::cout << cur_sum << " ";
    const auto it = std::find_if(
        cnt.begin(), cnt.end(), [cur_sum](const auto& i) { return i.first == cur_sum; });
    if (it != cnt.end()) {
      auto* prev = it->second;
      cnt.resize(it - cnt.begin() + 1);
      if (prev == nullptr) {
        head = cur->next;
      } else {
        prev->next = cur->next;
      }

    } else {
      cnt.emplace_back(cur_sum, cur);
    }
    cur = cur->next;
  }
  return head;
}
}  // namespace standard

}  // namespace leetcode::removezerosumconsecutivenodesfromlinkedlist