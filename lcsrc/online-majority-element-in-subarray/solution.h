#pragma once

#include "lcsrc/lib/stlplus.h"

namespace leetcode::onlinemajorityelementinsubarray {

class MajorityChecker {
public:
  explicit MajorityChecker(const std::vector<int>& arr );

  bool query(const int& left ,const int& right ,const int& threshold );

  static std::shared_ptr<MajorityChecker> Build(const std::vector<int>& arr ) {
    return std::make_shared<MajorityChecker>(arr );
  }
};
}  // namespace leetcode::onlinemajorityelementinsubarray