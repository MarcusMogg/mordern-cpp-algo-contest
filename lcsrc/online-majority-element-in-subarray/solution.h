#pragma once

#include <utility>
#include <vector>

#include "lcsrc/lib/stlplus.h"

namespace leetcode::onlinemajorityelementinsubarray {

class MajorityChecker {
 public:
  explicit MajorityChecker(const std::vector<int>& arr);

  int query(const int& left, const int& right, const int& threshold);

  static std::shared_ptr<MajorityChecker> Build(const std::vector<int>& arr) {
    return std::make_shared<MajorityChecker>(arr);
  }

  int QueryCnt(int val, int left, int right);
  void BuildTree(const std::vector<int>& arr, int s, int t, int p);
  std::pair<int, int> Query(int l, int r, int cl, int cr, int p);

  static int Left(int p) { return p * 2; }
  static int Right(int p) { return p * 2 + 1; }

  std::vector<std::pair<int, int>> tree;
  std::map<int, std::vector<int>> index;
  int end_;
};
}  // namespace leetcode::onlinemajorityelementinsubarray