#pragma once

#include <algorithm>
#include <array>
#include <cctype>
#include <concepts>
#include <cstddef>
#include <format>
#include <functional>
#include <iostream>
#include <iterator>
#include <memory>
#include <optional>
#include <queue>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>
#include <xutility>

#include "leetcode_struct.h"
#include "token.h"

namespace leetcode::lib {
using InputType = SimpleGenerator<Token>::iterator;

template <class T, class It>
concept CanParse = requires(std::remove_cvref_t<T> obj) {
  requires std::default_initializable<typename std::remove_cvref_t<T>>;
  requires std::default_initializable<typename std::remove_cvref_t<T>::DataType>;
  requires std::input_iterator<It>;

  requires requires(It test_cases) {
    { obj.Parse(test_cases) } -> std::same_as<typename std::remove_cvref_t<T>::DataType>;
  };
};

// do nothing
struct EmptyParser {
  using DataType = char;

  static DataType Parse(InputType /* ignore */) { return ' '; }
};

template <CanParse<InputType> SplitParser, CanParse<InputType>... Parser>
struct TestCase {
  using DataType = std::tuple<typename Parser::DataType...>;

  std::tuple<Parser...> parsers;

  template <CanParse<InputType> T, CanParse<InputType>... Args>
  static auto ParseImpl(InputType test_cases, T&& cur, Args&&... args) {
    auto tmp = std::tuple<typename std::remove_cvref_t<T>::DataType>{cur.Parse(test_cases)};
    if constexpr (sizeof...(args) == 0) {
      return tmp;
    } else {
      SplitParser{}.Parse(test_cases);
      return std::tuple_cat(tmp, ParseImpl(test_cases, std::forward<Args>(args)...));
    }
  }

  DataType Parse(InputType test_cases) const {
    return std::apply(
        [&test_cases](const Parser&... parser_list) {
          return ParseImpl(test_cases, parser_list...);
        },
        parsers);
  }
};

struct IntParser {
  using DataType = int;

  [[nodiscard]] static DataType Parse(InputType test_cases) {
    const auto& token = *test_cases;
    if (token.type != Token::TokenType::kInteger) {
      throw ParseError(std::format("expected kInteger | real {}", token.raw_data));
    }
    int res = std::stoi(std::string(token.raw_data));
    test_cases++;
    return res;
  }
};

template <CanParse<InputType> T>
struct VectorParser {
  using DataType = std::vector<typename T::DataType>;

  [[nodiscard]] static DataType Parse(InputType test_cases) {
    DataType res;
    auto& token = *test_cases;
    if (token.type != Token::TokenType::kSquareBracketsLeft) {
      throw ParseError("expected kSquareBracketsLeft in VectorParser begin");
    }

    test_cases++;
    token = *test_cases;

    T data_parser;
    while (true) {
      if (token.type == Token::TokenType::kSquareBracketsRight) {
        break;
      }
      res.emplace_back(data_parser.Parse(test_cases));
      token = *test_cases;
      if (token.type == Token::TokenType::kSquareBracketsRight) {
        break;
      }
      if (token.type != Token::TokenType::kComma) {
        throw ParseError("expected kComma in VectorParser");
      }
      test_cases++;
      token = *test_cases;
    }
    test_cases++;
    return res;
  }
};

struct StringParser {
  using DataType = std::string;

  [[nodiscard]] static DataType Parse(InputType test_cases) {
    const auto& token = *test_cases;
    if (token.type != Token::TokenType::kString) {
      throw ParseError("expected kString");
    }
    auto res = std::string(token.raw_data);
    test_cases++;
    return res;
  }
};

struct BoolParser {
  using DataType = bool;

  [[nodiscard]] static DataType Parse(InputType test_cases) {
    const auto& token = *test_cases;
    if (token.type != Token::TokenType::kBool) {
      throw ParseError("expected kString");
    }
    std::string lower;
    std::transform(
        token.raw_data.begin(), token.raw_data.end(), std::back_inserter(lower), ::tolower);
    bool res;
    if (lower == "true") {
      res = true;
    } else if (lower == "false") {
      res = false;
    } else {
      throw ParseError(std::format("unexpected string {}", lower));
    }
    test_cases++;
    return res;
  }
};

struct CommaParser {
  using DataType = char;

  static DataType Parse(InputType test_cases) {
    auto& token = *test_cases;
    if (token.type != Token::TokenType::kComma) {
      throw ParseError("expected kComma in VectorParser");
    }
    test_cases++;
    return ',';
  }
};

template <size_t N>
struct StringLiteral {
  // NOLINTNEXTLINE (cppcoreguidelines-avoid-c-arrays)
  constexpr StringLiteral(const char (&str)[N]) { std::copy_n(str, N, value.begin()); }
  std::array<char, N> value;

  [[nodiscard]] constexpr size_t size() const noexcept { return value.size(); }
};

template <StringLiteral Key, class Value>
struct ComplieTimePair {
  using type = Value;

  static ComplieTimePair GetPair(
      std::integral_constant<StringLiteral<Key.size()>, Key> /* unused */) {
    return {};
  }
};

template <typename... Pairs>
struct ComplieTimeMap : public Pairs... {
  using Pairs::GetPair...;

  template <StringLiteral Key>
  using find_type =
      typename decltype(GetPair(std::integral_constant<StringLiteral<Key.size()>, Key>{}))::type;
};

template <class Cm>
struct DynamicTestCase {
  using DataType = std::vector<std::string>;

  static DataType Parse(InputType test_cases) {
    // first line
    auto res = VectorParser<StringParser>::Parse(test_cases);
    auto& token = *test_cases;
    if (token.type != Token::TokenType::kSquareBracketsLeft) {
      throw ParseError("expected kSquareBracketsLeft in Second line");
    }
    test_cases++;
    return res;
  }

  template <StringLiteral Key, class Func>
  static void Run(InputType test_cases, Func&& f) {
    using Parser = typename Cm::template find_type<Key>;
    static_assert(CanParse<Parser, InputType>, "Can't parse before run");

    // begin with [
    auto& token = *test_cases;
    if (token.type != Token::TokenType::kSquareBracketsLeft) {
      throw ParseError("expected kSquareBracketsLeft");
    }
    test_cases++;
    std::invoke(f, Parser{}.Parse(test_cases));

    token = *test_cases;
    // end with ]
    if (token.type != Token::TokenType::kSquareBracketsRight) {
      throw ParseError(std::format("expected kSquareBracketsRight | real {}", token.raw_data));
    }
    test_cases++;
    token = *test_cases;

    // , or ] after each case
    if (!Among(token.type, Token::TokenType::kComma, Token::TokenType::kSquareBracketsRight)) {
      throw ParseError("expected kComma or kSquareBracketsRight after parse");
    }
    test_cases++;
  }
};

template <CanParse<InputType> T>
struct NullableParser {
  using DataType = std::optional<typename T::DataType>;

  [[nodiscard]] static DataType Parse(InputType test_cases) {
    auto& token = *test_cases;
    if (token.type == Token::TokenType::kNull) {
      test_cases++;
      return {};
    }
    return T{}.Parse(test_cases);
  }
};

template <CanParse<InputType> T>
struct TreeParser {
  using RealDataType = std::vector<typename NullableParser<T>::DataType>;
  // using TreeType = TreeNode<typename T::DataType>;
  using TreeType = TreeNode;
  using DataType = TreeType*;

  [[nodiscard]] static RealDataType ParseRawData(InputType test_cases) {
    return VectorParser<NullableParser<T>>::Parse(test_cases);
  }

  static DataType Parse(InputType test_cases) {
    const auto raw_data = ParseRawData(test_cases);
    auto* root = new TreeType();
    std::queue<std::reference_wrapper<TreeType*>> q;
    auto it = raw_data.begin();
    q.emplace(root);
    while (it != raw_data.end() && !q.empty()) {
      auto front = q.front();
      if (it->has_value()) {
        if (front == nullptr) {
          front.get() = new TreeType();
        }
        front.get()->val = it->value();
        q.emplace(front.get()->left);
        q.emplace(front.get()->right);
      }
      q.pop();
      ++it;
    }
    return root;
  }
};

}  // namespace leetcode::lib
