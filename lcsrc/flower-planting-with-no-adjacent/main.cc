// https://leetcode.cn/problems/flower-planting-with-no-adjacent
#include "lcsrc/lib/io_helper.h"
#include "lcsrc/lib/parser.h"
#include "solution.h"

using namespace leetcode::lib;

int main(int /*argc*/, const char** argv) {
  auto test_cases = ReadFile(argv[1]);

  TestCase<EmptyParser, IntParser, VectorParser<VectorParser<IntParser>>> parse;

  auto next_token = NextToken(test_cases);
  auto it = next_token.begin();
  try {
    while (it != next_token.end()) {
      const auto input = parse.Parse(it);
      std::cout << "input:\n";
      print(input);

      std::cout << "expected:\n";
      std::cout << std::apply(leetcode::flowerplantingwithnoadjacent::standard::Solve, input)
                << "\n";

      std::cout << "ouput:\n";
      std::cout << std::apply(leetcode::flowerplantingwithnoadjacent::Solve, input) << "\n";
    }
  } catch (const std::exception& e) {
    std::cout << e.what();
  }

  return 0;
}
