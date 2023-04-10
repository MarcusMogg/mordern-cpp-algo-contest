#pragma once

#include <filesystem>
#include <iostream>
#include <vector>

namespace leetcode::lib {

template <class T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v) {
  out << '[';
  if (!v.empty()) {
    std::ranges::copy(v, std::ostream_iterator<T>(out, ", "));
    out << "\b\b";  // use two ANSI backspace characters '\b' to overwrite final ", "
  }
  out << "]";
  return out;
}

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

std::string ReadFile(const std::filesystem::path& path);
}  // namespace leetcode::lib
