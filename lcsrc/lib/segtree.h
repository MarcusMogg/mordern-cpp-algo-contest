#pragma once

#include <vector>

template <typename T>
class SegTreeLazyRangeAdd {
 public:
  explicit SegTreeLazyRangeAdd<T>(const std::vector<T>& v)
      : end_(v.size() - 1), tree_(v.size() * 4, 0), lazy_(v.size() * 4, 0) {
    Build(0, end_, 1);
  }

  // [l,r] close
  T RangeSum(int l, int r) { return RangeSum(l, r, 0, end_ - 1, kRoot); }

  // [l,r] close
  void RangeAdd(int l, int r, int val) { RangeAdd(l, r, val, 0, end_ - 1, kRoot); }

  static int Left(int p) { return p * 2; }
  static int Right(int p) { return p * 2 + 1; }

 private:
  int end_;
  std::vector<T> tree_;
  std::vector<T> lazy_;  // add value to [l,r)

  static constexpr int kRoot = 1;

  // update tree_ from lazy_ value
  void Maintain(int cl, int cr, int p) {
    int cm = cl + (cr - cl) / 2;
    if (cl != cr && lazy_[p]) {
      lazy_[Left(p)] += lazy_[p];
      lazy_[Right(p)] += lazy_[p];
      tree_[Left(p)] += lazy_[p] * (cm - cl + 1);
      tree_[Right(p)] += lazy_[p] * (cr - cm);
      lazy_[p] = 0;
    }
  }

  T RangeSum(int l, int r, int cl, int cr, int p) {
    if (l <= cl && cr <= r) {
      return tree_[p];
    }
    int m = cl + (cr - cl) / 2;
    T sum = 0;
    Maintain(cl, cr, p);
    if (l <= m) {
      sum += RangeSum(l, r, cl, m, Left(p));
    }
    if (r > m) {
      sum += RangeSum(l, r, m + 1, cr, Right(p));
    }
    return sum;
  }

  void RangeAdd(int l, int r, T val, int cl, int cr, int p) {
    if (l <= cl && cr <= r) {
      lazy_[p] += val;
      tree_[p] += (cr - cl + 1) * val;
      return;
    }
    int m = cl + (cr - cl) / 2;
    Maintain(cl, cr, p);
    if (l <= m) {
      RangeAdd(l, r, val, cl, m, Left(p));
    }
    if (r > m) {
      RangeAdd(l, r, val, m + 1, cr, Right(p));
    }
    tree_[p] = tree_[Left(p)] + tree_[Right(p)];
  }

  // arr[s:t) , tree node p
  void Build(const std::vector<T>& arr, int s, int t, int p) {
    if (s == t) {
      tree_[p] = arr[s];
      return;
    }
    int m = s + (t - s) / 2;
    Build(arr, s, m, Left(p));
    Build(arr, m + 1, t, Right(p));
    tree_[p] = tree_[Left(p)] + tree_[Right(p)];
  }
};