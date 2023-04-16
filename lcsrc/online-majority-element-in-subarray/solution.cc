#include "solution.h"

#include <algorithm>
#include <iostream>
#include <vector>

namespace leetcode::onlinemajorityelementinsubarray {

MajorityChecker::MajorityChecker(const std::vector<int>& arr)
    : tree(arr.size() * 4, {0, 0}), end_(static_cast<int>(arr.size()) - 1) {
  for (int i = 0; i < arr.size(); ++i) {
    index[arr[i]].emplace_back(i);
  }
  BuildTree(arr, 0, end_, 1);
}

int MajorityChecker::QueryCnt(int val, int left, int right) {
  return static_cast<int>(
      std::upper_bound(index[val].begin(), index[val].end(), right) -
      std::lower_bound(index[val].begin(), index[val].end(), left));
}
void MajorityChecker::BuildTree(const std::vector<int>& arr, int s, int t, int p) {
  if (s == t) {
    tree[p] = {arr[t], 1};
    return;
  }
  int m = s + (t - s) / 2;
  BuildTree(arr, s, m, Left(p));
  BuildTree(arr, m + 1, t, Right(p));

  if (tree[Left(p)].first != tree[Right(p)].first) {
    int ltimes = tree[Left(p)].second;
    int rtimes = tree[Right(p)].second;
    if (ltimes >= rtimes) {
      tree[p] = tree[Left(p)];
      tree[p].second -= rtimes;
    } else {
      tree[p] = tree[Right(p)];
      tree[p].second -= ltimes;
    }
  } else {
    tree[p] = tree[Right(p)];
    tree[p].second += tree[Left(p)].second;
  }
}

std::pair<int, int> MajorityChecker::Query(int l, int r, int cl, int cr, int p) {
  std::cout << l << " " << r << " " << cl << " " << cr << " " << p << "\n";
  if (l <= cl && cr <= r) {
    std::cout << "out" << tree[p].first << tree[p].second << "\n";
    return tree[p];
  }
  int m = cl + (cr - cl) / 2;

  std::pair<int, int> res{0, 0};
  if (l <= m) {
    res = Query(l, r, cl, m, Left(p));
  }
  if (r > m) {
    auto rv = Query(l, r, m + 1, cr, Right(p));
    if (res.first != rv.first && rv.first != 0) {
      if (rv.second > res.second) {
        res = {rv.first, rv.second - res.second};
      } else {
        res = {res.first, res.second - rv.second};
      }
    } else {
      res.second += rv.second;
    }
  }
  return res;
}

int MajorityChecker::query(const int& left, const int& right, const int& threshold) {
  int val = Query(left, right, 0, end_, 1).first;
  std::cout << val << "\n";
  std::cout << QueryCnt(val, left, right) << "\n";
  if (QueryCnt(val, left, right) >= threshold) {
    return val;
  }
  return -1;
}

}  // namespace leetcode::onlinemajorityelementinsubarray