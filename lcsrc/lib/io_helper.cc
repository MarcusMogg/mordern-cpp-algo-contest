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
}  // namespace leetcode::lib