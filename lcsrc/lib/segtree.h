#pragma once

#include <concepts>
#include <type_traits>
#include <vector>

template <class T>
concept SegTreeNode = requires(T cur_right) {
  requires std::is_default_constructible_v<T>;
  requires std::is_copy_assignable_v<T>;
  requires std::equality_comparable<T>;

  requires requires(T another) { cur_right += another; };
  requires requires(T another) { cur_right + another; };
  requires requires() { cur_right * 2; };
};

template <SegTreeNode T>
class SegTreeLazyRangeAdd {
 public:
  explicit SegTreeLazyRangeAdd<T>(const std::vector<T>& v)
      : end_(static_cast<int>(v.size()) - 1), tree_(v.size() * 4, T{}), lazy_(v.size() * 4, T{}) {
    Build(v, 0, end_, kRoot);
  }

  // [l,r] close
  T RangeSum(int l, int r) { return RangeSum(l, r, 0, end_, kRoot); }

  // [l,r] close
  void RangeAdd(int l, int r, int val) { RangeAdd(l, r, val, 0, end_, kRoot); }

  static int Left(int tree_id) { return tree_id * 2; }
  static int Right(int tree_id) { return tree_id * 2 + 1; }

 private:
  int end_;
  std::vector<T> tree_;
  std::vector<T> lazy_;  // add value to [l,r)

  static constexpr int kRoot = 1;

  // update tree_ from lazy_ value
  void Maintain(int cur_left, int cur_right, int tree_id) {
    int cm = cur_left + (cur_right - cur_left) / 2;
    if (cur_left != cur_right && lazy_[tree_id] != T{}) {
      lazy_[Left(tree_id)] += lazy_[tree_id];
      lazy_[Right(tree_id)] += lazy_[tree_id];
      tree_[Left(tree_id)] += lazy_[tree_id] * (cm - cur_left + 1);
      tree_[Right(tree_id)] += lazy_[tree_id] * (cur_right - cm);
      lazy_[tree_id] = T{};
    }
  }

  T RangeSum(int l, int r, int cur_left, int cur_right, int tree_id) {
    if (l <= cur_left && cur_right <= r) {
      return tree_[tree_id];
    }
    int m = cur_left + (cur_right - cur_left) / 2;
    T sum{};
    // Maintain(cur_left, cur_right, tree_id);
    if (l <= m) {
      sum += RangeSum(l, r, cur_left, m, Left(tree_id));
    }
    if (r > m) {
      sum += RangeSum(l, r, m + 1, cur_right, Right(tree_id));
    }
    return sum;
  }

  void RangeAdd(int l, int r, T val, int cur_left, int cur_right, int tree_id) {
    if (l <= cur_left && cur_right <= r) {
      lazy_[tree_id] += val;
      tree_[tree_id] += (cur_right - cur_left + 1) * val;
      return;
    }
    int m = cur_left + (cur_right - cur_left) / 2;
    Maintain(cur_left, cur_right, tree_id);
    if (l <= m) {
      RangeAdd(l, r, val, cur_left, m, Left(tree_id));
    }
    if (r > m) {
      RangeAdd(l, r, val, m + 1, cur_right, Right(tree_id));
    }
    tree_[tree_id] = tree_[Left(tree_id)] + tree_[Right(tree_id)];
  }

  // arr[cur_left:cur_right) , tree node tree_id
  void Build(const std::vector<T>& arr, int cur_left, int cur_right, int tree_id) {
    if (cur_left == cur_right) {
      tree_[tree_id] = arr[cur_left];
      return;
    }
    int m = cur_left + (cur_right - cur_left) / 2;
    Build(arr, cur_left, m, Left(tree_id));
    Build(arr, m + 1, cur_right, Right(tree_id));
    tree_[tree_id] = tree_[Left(tree_id)] + tree_[Right(tree_id)];
  }
};