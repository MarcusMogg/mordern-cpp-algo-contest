#pragma once

#include <set>
#include <stack>
#include <vector>

#include "lcsrc/lib/stlplus.h"

namespace leetcode::dinnerplatestacks {

class DinnerPlates {
 public:
  explicit DinnerPlates(int capacity);

  void push(int val);

  int pop();

  int popAtStack(int index);

  static std::shared_ptr<DinnerPlates> Build(int capacity) {
    return std::make_shared<DinnerPlates>(capacity);
  }

 private:
  int cap_;
  std::set<int> not_empty_;
  std::vector<std::vector<int>> stacks_;

  [[nodiscard]] int size() const { return static_cast<int>(stacks_.size()); }
};
}  // namespace leetcode::dinnerplatestacks