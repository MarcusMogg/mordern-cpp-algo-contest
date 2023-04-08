#include <filesystem>
#include <fstream>
#include <iostream>

#include "lcsrc/lib/output_helper.h"
#include "lcsrc/lib/parser.h"

using namespace std;

auto ReadFile(const std::filesystem::path& path) -> std::string {
  constexpr std::size_t kReadSize = 4096;
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

int main() {
  auto test_cases = ReadFile("./simple_test_cases");

  leetcode::lib::
      TestCase<leetcode::lib::VectorParser<leetcode::lib::IntParser>, leetcode::lib::IntParser>
          parse;

  auto next_token = leetcode::lib::NextToken(test_cases);
  auto it = next_token.begin();
  while (it != next_token.end()) {
    print(parse.Parse(it));
  }
  return 0;
}
