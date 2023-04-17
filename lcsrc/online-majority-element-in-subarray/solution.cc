#include "solution.h"

#include <algorithm>
#include <iostream>
#include <vector>

namespace leetcode::onlinemajorityelementinsubarray {

std::vector<Node> ConverArrToNode(const std::vector<int>& arr) {
  std::vector<Node> arr_node(arr.size());
  for (int i = 0; i < arr.size(); ++i) {
    arr_node[i] = {arr[i], 1};
  }
  return arr_node;
}

MajorityChecker::MajorityChecker(const std::vector<int>& arr) : tree_(ConverArrToNode(arr)) {
  for (int i = 0; i < arr.size(); ++i) {
    index[arr[i]].emplace_back(i);
  }
}

int MajorityChecker::QueryCnt(int val, int left, int right) {
  return static_cast<int>(
      std::upper_bound(index[val].begin(), index[val].end(), right) -
      std::lower_bound(index[val].begin(), index[val].end(), left));
}
int MajorityChecker::query(const int& left, const int& right, const int& threshold) {
  int val = tree_.RangeSum(left, right).value;
  if (QueryCnt(val, left, right) >= threshold) {
    return val;
  }
  return -1;
}

}  // namespace leetcode::onlinemajorityelementinsubarray