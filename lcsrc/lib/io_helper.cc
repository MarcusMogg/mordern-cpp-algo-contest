#include "io_helper.h"

#include <fstream>

namespace leetcode::lib {
std::string ReadFile(const std::filesystem::path& path) {
  static constexpr std::size_t kReadSize = 4096;
  auto stream = std::ifstream(path.c_str());
  stream.exceptions(std::ios_base::badbit);

  auto out = std::string();
  auto buf = std::string(kReadSize, '\0');
  while (stream.read(buf.data(), kReadSize)) {
    out.append(buf, 0, stream.gcount());
  }
  out.append(buf, 0, stream.gcount());
  return out;
}

std::ostream& operator<<(std::ostream& out, const TreeNode* v) {
  out << '[';

  std::queue<const TreeNode*> q;
  q.emplace(v);
  while (!q.empty()) {
    const auto* c = q.front();
    if (c != nullptr) {
      out << c->val << ", ";
      q.emplace(c->left);
      q.emplace(c->right);
    } else {
      out << "null, ";
    }
    q.pop();
  }
  out << "\b\b";
  out << "]";
  return out;
}
}  // namespace leetcode::lib