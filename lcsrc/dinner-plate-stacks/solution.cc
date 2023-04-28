#include "solution.h"

#include <stack>

namespace leetcode::dinnerplatestacks {

DinnerPlates::DinnerPlates(int capacity) : cap_(capacity) {}

void DinnerPlates::push(int val) {
  if (not_empty_.empty()) {
    not_empty_.emplace(size());
    stacks_.emplace_back();
  }
  int cur = *not_empty_.begin();
  stacks_[cur].push_back(val);

  if (stacks_[cur].size() >= cap_) {
    not_empty_.erase(cur);
  }
}
int DinnerPlates::pop() {
  while (!stacks_.empty() && stacks_.back().empty()) {
    stacks_.pop_back();
    not_empty_.erase(size());
  }
  if (stacks_.empty() || stacks_.back().empty()) {
    return -1;
  }
  int res = stacks_.back().back();
  stacks_.back().pop_back();
  not_empty_.emplace(size() - 1);
  return res;
}
int DinnerPlates::popAtStack(int index) {
  if (index >= size()) {
    return -1;
  }

  if (stacks_[index].empty()) {
    return -1;
  }
  int res = stacks_[index].back();
  stacks_[index].pop_back();
  not_empty_.emplace(index);

  return res;
}

}  // namespace leetcode::dinnerplatestacks