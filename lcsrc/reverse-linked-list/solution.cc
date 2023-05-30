#include "solution.h"

namespace leetcode::reverselinkedlist {

ListNode* Solve(ListNode* head) {
  const auto reverse = [](this auto&& reverse, ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
      return std::pair{head, head};
    }
    const auto [new_head, new_end] = reverse(head->next);
    new_end->next = head;
    head->next = nullptr;
    return std::pair{new_head, head};
  };
  return reverse(head).first;
}

namespace standard {
ListNode* Solve(ListNode* head) {
  const auto reverse = [](auto&& reverse, ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
      return std::pair{head, head};
    }
    const auto [new_head, new_end] = reverse(reverse, head->next);
    new_end->next = head;
    head->next = nullptr;
    return std::pair{new_head, head};
  };
  return reverse(reverse, head).first;
}
}  // namespace standard

}  // namespace leetcode::reverselinkedlist