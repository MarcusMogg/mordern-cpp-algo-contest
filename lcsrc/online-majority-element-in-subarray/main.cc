// https://leetcode.cn/problems/online-majority-element-in-subarray
#include "lcsrc/lib/io_helper.h"
#include "lcsrc/lib/parser.h"
#include "solution.h"

using namespace leetcode::lib;
using namespace leetcode::onlinemajorityelementinsubarray;

int main(int /*argc*/, const char** argv) {
  auto test_cases = ReadFile(argv[1]);
  auto next_token = NextToken(test_cases);
  auto it = next_token.begin();

  // for constructor
  using MajorityCheckerParser = TestCase<CommaParser, VectorParser<IntParser>>;
  using queryParser = TestCase<CommaParser, IntParser, IntParser, IntParser>;

  using Parser = DynamicTestCase<ComplieTimeMap<
      ComplieTimePair<"query", queryParser>,
      ComplieTimePair<"MajorityChecker", MajorityCheckerParser>>>;

  try {
    while (it != next_token.end()) {
      const auto input = Parser::Parse(it);
      std::shared_ptr<MajorityChecker> solution;

      for (const auto& i : input) {
        if (i == "MajorityChecker") {
          Parser::Run<"MajorityChecker">(it, [&solution](MajorityCheckerParser::DataType&& input) {
            std::cout << "input:\n";
            print(input);
            solution = std::apply(MajorityChecker::Build, input);
          });
        } else if (i == "query") {
          Parser::Run<"query">(it, [&solution](queryParser::DataType&& input) {
            std::cout << "input:\n";
            print(input);
            std::cout << "ouput:\n";
            auto res = std::apply(
                &MajorityChecker::query, std::tuple_cat(std::make_tuple(*solution), input));
            std::cout << res << "\n";
          });
        }
      }
    }
  } catch (const std::exception& e) {
    std::cout << e.what();
  }

  return 0;
}
