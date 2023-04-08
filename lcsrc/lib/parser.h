#pragma once

#include <concepts>
#include <cstddef>
#include <functional>
#include <iostream>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>
#include <xutility>

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

template <CanParse<InputType>... Parser>
struct TestCase {
  using DataType = std::tuple<typename Parser::DataType...>;

  std::tuple<Parser...> parsers;

  template <CanParse<InputType> T, CanParse<InputType>... Args>
  static auto ParseImpl(InputType test_cases, T&& cur, Args&&... args) {
    auto tmp = std::tuple<typename std::remove_cvref_t<T>::DataType>{cur.Parse(test_cases)};
    if constexpr (sizeof...(args) == 0) {
      return tmp;
    } else {
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
      throw ParseError("expected kInteger");
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

}  // namespace leetcode::lib
