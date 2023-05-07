// https://leetcode.cn/problems/pairs-of-songs-with-total-durations-divisible-by-60
#include "lcsrc/lib/io_helper.h"
#include "lcsrc/lib/parser.h"
#include "solution.h"

using namespace leetcode::lib;
using namespace leetcode::pairsofsongswithtotaldurationsdivisibleby60;

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
                       leetcode::pairsofsongswithtotaldurationsdivisibleby60::standard::Solve,
                       input)
                << "\n";

      std::cout << "ouput:\n";
      std::cout << std::apply(leetcode::pairsofsongswithtotaldurationsdivisibleby60::Solve, input)
                << "\n";
    }
  } catch (const std::exception& e) {
    std::cout << e.what();
  }

  return 0;
}
