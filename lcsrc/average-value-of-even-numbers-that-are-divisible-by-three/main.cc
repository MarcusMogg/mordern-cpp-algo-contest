// https://leetcode.cn/problems/average-value-of-even-numbers-that-are-divisible-by-three
#include "lcsrc/lib/io_helper.h"
#include "lcsrc/lib/parser.h"
#include "solution.h"

using namespace leetcode::lib;
using namespace leetcode::averagevalueofevennumbersthataredivisiblebythree;

int main(int /*argc*/, const char** argv) {
  auto test_cases = ReadFile(argv[1]);
  auto next_token = NextToken(test_cases);
  auto it = next_token.begin();

  TestCase<EmptyParser, VectorParser<IntParser>> parse;

  try {
    while (it != next_token.end()) {
      const auto input = parse.Parse(it);
      std::cout << "input:\n";
      print(input);

      std::cout << "expected:\n";
      std::cout << std::apply(
                       leetcode::averagevalueofevennumbersthataredivisiblebythree::standard::Solve,
                       input)
                << "\n";

      std::cout << "ouput:\n";
      std::cout << std::apply(
                       leetcode::averagevalueofevennumbersthataredivisiblebythree::Solve, input)
                << "\n";
    }
  } catch (const std::exception& e) {
    std::cout << e.what();
  }

  return 0;
}
