#pragma once

#include <complex>
#include <utility>
#include <vector>

#include "lcsrc/lib/stlplus.h"

namespace leetcode::onlinemajorityelementinsubarray {

struct Node {
  int value{0};
  int cnt{0};

  Node& operator+=(const Node& right) {
    if (right.value == value) {
      cnt += right.cnt;
    } else {
      if (right.cnt > cnt) {
        value = right.value;
      }
      cnt = std::abs(right.cnt - cnt);
    }
    return *this;
  }

  Node operator+(const Node& right) const {
    Node res = *this;
    res += right;
    return res;
  }

  Node operator*(int /*right*/) const { return *this; }

  bool operator==(const Node& right) const { return value == right.value && cnt == right.cnt; }
};

class MajorityChecker {
 public:
  explicit MajorityChecker(const std::vector<int>& arr);

  int query(const int& left, const int& right, const int& threshold);

  static std::shared_ptr<MajorityChecker> Build(const std::vector<int>& arr) {
    return std::make_shared<MajorityChecker>(arr);
  }

  int QueryCnt(int val, int left, int right);

  std::map<int, std::vector<int>> index;

  SegTreeLazyRangeAdd<Node> tree_;
};
}  // namespace leetcode::onlinemajorityelementinsubarray