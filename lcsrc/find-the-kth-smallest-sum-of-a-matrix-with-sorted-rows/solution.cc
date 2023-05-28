#include "solution.h"

#include <vcruntime.h>

#include <algorithm>
#include <queue>
#include <vector>

namespace leetcode::findthekthsmallestsumofamatrixwithsortedrows {

int Solve(const std::vector<std::vector<int>>& mat, int k) {
  // TODO(): your solution here
  return {};
}

namespace standard {

std::vector<int> MergeQueue(const std::vector<int>& q1, const std::vector<int>& q2, int k) {
  std::vector<int> res;
  res.reserve(q1.size() * q2.size());
  for (const auto& i : q1) {
    for (const auto& j : q2) {
      res.emplace_back(i + j);
    }
  }
  std::sort(res.begin(), res.end());
  res.resize(std::min<size_t>(k, res.size()));
  return res;
}

int Solve(const std::vector<std::vector<int>>& mat, int k) {
  if (mat.size() == 1) {
    return mat[0][k - 1];
  }
  std::vector<int> q = MergeQueue(mat[0], mat[1], k);
  for (int i = 2; i < mat.size(); ++i) {
    q = MergeQueue(q, mat[i], k);
  }

  return q.back();
}
}  // namespace standard

}  // namespace leetcode::findthekthsmallestsumofamatrixwithsortedrows