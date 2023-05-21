#include "solution.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <ranges>

namespace leetcode::o8SXZn {

int Solve(const std::vector<int>& bucket, const std::vector<int>& vat) {
  int maxk = std::ranges::max(vat);
  if (maxk == 0) {
    return 0;
  }
  using namespace std::ranges;
  return std::ranges::min(views::iota(1, maxk + 1) | views::transform([&](int k) {
                            return std::ranges::fold_left(
                                views::zip(vat, bucket) | views::transform([k](const auto& item) {
                                  const auto [v, b] = item;
                                  return std::ranges::max(0, (v - 1) / k + 1 - b);
                                }),
                                k,
                                std::plus<>());
                          }));
}

namespace standard {
int Solve(const std::vector<int>& bucket, const std::vector<int>& vat) {
  int maxk = *std::max_element(vat.begin(), vat.end());
  if (maxk == 0) {
    return 0;
  }
  int res = std::numeric_limits<int>::max();
  for (int k = 1; k <= maxk && k < res; ++k) {
    int t = 0;
    for (int i = 0; i < bucket.size(); ++i) {
      t += std::max(0, (vat[i] + k - 1) / k - bucket[i]);
    }
    res = std::min(res, t + k);
  }
  return res;
}

}  // namespace standard

}  // namespace leetcode::o8SXZn