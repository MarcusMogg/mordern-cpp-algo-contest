#pragma once

#include <concepts>
#include <cstddef>
#include <functional>
#include <iostream>
#include <span>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

namespace leetcode::lib {
using InputType = std::span<std::string_view>;

template <class T>
concept CanParse = requires(std::remove_cvref_t<T> obj) {
  requires std::default_initializable<typename std::remove_cvref_t<T>::DataType>;

  requires requires(const InputType test_cases) {
    { obj.Parse(test_cases) } -> std::same_as<InputType>;
  };

  requires requires {
    { obj.GetData() } -> std::same_as<typename std::remove_cvref_t<T>::DataType>;
  };
};

template <CanParse T, CanParse... Args>
auto GetDataImpl(T&& cur, Args&&... args) {
  if constexpr (sizeof...(args) == 0) {
    return std::tuple<typename std::remove_cvref_t<T>::DataType>{cur.GetData()};
  } else {
    return std::tuple_cat(cur.GetData(), GetDataImpl(std::forward<Args>(args)...));
  }
}

template <CanParse... Parser>
struct TestCase {
  using DataType = std::tuple<typename Parser::DataType...>;

  std::tuple<Parser...> parsers;

  template <CanParse T, CanParse... Args>
  static InputType ParseImpl(const InputType test_cases, T&& cur, Args&&... args) {
    if constexpr (sizeof...(args) == 0) {
      return cur.Parse(test_cases);
    } else {
      return ParseImpl(cur.Parse(test_cases), std::forward<Args>(args)...);
    }
  }

  InputType Parse(const InputType test_cases) {
    return std::apply(
        [&test_cases]<CanParse... Args>(Args&&... parser_list) {
          return std::invoke(ParseImpl, test_cases, std::forward<Args>(parser_list)...);
        },
        parsers);
  }

  [[nodiscard]] DataType GetData() const {
    return std::apply(
        [&](const Parser&... parser_list) { return GetDataImpl(parser_list...); }, parsers);
  }
};

struct IntParser {
  using DataType = int;
  DataType data{0};

  InputType Parse(const InputType test_cases) {
    if (test_cases.empty()) {
      throw "Parse int data error";
    }
    data = std::stoi(std::string(test_cases[0]));
    return test_cases.subspan(1);
  }

  [[nodiscard]] DataType GetData() const { return data; }
};

}  // namespace leetcode::lib

template <class Tuple, std::size_t N>
struct TuplePrinter {
  static void print(const Tuple& t) {
    TuplePrinter<Tuple, N - 1>::print(t);
    std::cout << ", " << std::get<N - 1>(t);
  }
};

template <class Tuple>
struct TuplePrinter<Tuple, 1> {
  static void print(const Tuple& t) { std::cout << std::get<0>(t); }
};

template <typename... Args, std::enable_if_t<sizeof...(Args) == 0, int> = 0>
void print(const std::tuple<Args...>& /*t*/) {
  std::cout << "()\n";
}

template <typename... Args, std::enable_if_t<sizeof...(Args) != 0, int> = 0>
void print(const std::tuple<Args...>& t) {
  std::cout << "(";
  TuplePrinter<decltype(t), sizeof...(Args)>::print(t);
  std::cout << ")\n";
}

void test() {
  using namespace leetcode::lib;

  TestCase<IntParser> t;

  std::vector<std::string_view> data = {"1", "2"};

  t.Parse(std::span{data});

  print(t.GetData());
}