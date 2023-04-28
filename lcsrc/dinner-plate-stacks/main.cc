// https://leetcode.cn/problems/dinner-plate-stacks
#include "lcsrc/lib/io_helper.h"
#include "lcsrc/lib/parser.h"
#include "solution.h"

using namespace leetcode::lib;
using namespace leetcode::dinnerplatestacks;

int main(int /*argc*/, const char** argv) {
  auto test_cases = ReadFile(argv[1]);
  auto next_token = NextToken(test_cases);
  auto it = next_token.begin();

  // for constructor
  using DinnerPlatesParser = TestCase<CommaParser, IntParser>;
  using pushParser = TestCase<CommaParser, IntParser>;
  using popParser = TestCase<CommaParser>;
  using popAtStackParser = TestCase<CommaParser, IntParser>;

  using Parser = DynamicTestCase<ComplieTimeMap<
      ComplieTimePair<"push", pushParser>,
      ComplieTimePair<"pop", popParser>,
      ComplieTimePair<"popAtStack", popAtStackParser>,
      ComplieTimePair<"DinnerPlates", DinnerPlatesParser>>>;

  try {
    while (it != next_token.end()) {
      const auto input = Parser::Parse(it);
      std::shared_ptr<DinnerPlates> solution;

      for (const auto& i : input) {
        std::cout << "----------------------\n";
        if (i == "DinnerPlates") {
          Parser::Run<"DinnerPlates">(it, [&solution](DinnerPlatesParser::DataType&& input) {
            solution = std::apply(DinnerPlates::Build, input);
          });
        } else if (i == "push") {
          Parser::Run<"push">(it, [&solution](pushParser::DataType&& input) {
            std::cout << "push input:\n";
            print(input);
            std::cout << "ouput:\nnull\n";
            std::apply(&DinnerPlates::push, std::tuple_cat(std::make_tuple(solution.get()), input));
          });
        } else if (i == "pop") {
          Parser::Run<"pop">(it, [&solution](popParser::DataType&& input) {
            std::cout << "pop input:\n";
            print(input);
            std::cout << "ouput:\n";
            auto res = std::apply(
                &DinnerPlates::pop, std::tuple_cat(std::make_tuple(solution.get()), input));
            std::cout << res << "\n";
          });
        } else if (i == "popAtStack") {
          Parser::Run<"popAtStack">(it, [&solution](popAtStackParser::DataType&& input) {
            std::cout << "popAtStack input:\n";
            print(input);
            std::cout << "ouput:\n";
            auto res = std::apply(
                &DinnerPlates::popAtStack, std::tuple_cat(std::make_tuple(solution.get()), input));
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
