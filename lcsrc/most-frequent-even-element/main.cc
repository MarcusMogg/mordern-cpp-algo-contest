// https://leetcode.cn/problems/most-frequent-even-element
#include "lcsrc/lib/io_helper.h"
#include "lcsrc/lib/parser.h"
#include "solution.h"

using namespace leetcode::lib;

int main(int /*argc*/, const char** argv) {
  auto test_cases = ReadFile(argv[1]);

  TestCase<VectorParser<IntParser>> parse;

  auto next_token = NextToken(test_cases);
  auto it = next_token.begin();
  while (it != next_token.end()) {
    const auto input = parse.Parse(it);
    std::cout << "input:\n";
    print(input);

    std::cout << "expected:\n";
    std::cout << std::apply(leetcode::mostfrequentevenelement::standard::Solve, input) << "\n";

    std::cout << "ouput:\n";
    std::cout << std::apply(leetcode::mostfrequentevenelement::Solve, input) << "\n";
  }
  return 0;
}
