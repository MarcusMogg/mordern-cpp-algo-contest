#pragma once

#include <algorithm>
#include <filesystem>
#include <functional>
#include <iostream>
#include <vector>

#include "leetcode_struct.h"

namespace leetcode::lib {

template <class Tuple, std::size_t N>
struct TuplePrinter {
  static void print(const Tuple& t) {
    TuplePrinter<Tuple, N - 1>::print(t);
    std::cout << ", " << std::get<N - 1>(t);
  }
  static void print(std::ostream& out, const Tuple& t) {
    TuplePrinter<Tuple, N - 1>::print(out, t);
    out << ", " << std::get<N - 1>(t);
  }
};

template <class Tuple>
struct TuplePrinter<Tuple, 1> {
  static void print(const Tuple& t) { std::cout << std::get<0>(t); }
  static void print(std::ostream& out, const Tuple& t) { out << std::get<0>(t); }
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

template <typename... Args, std::enable_if_t<sizeof...(Args) == 0, int> = 0>
std::ostream& operator<<(std::ostream& out, const std::tuple<Args...>& /**/) {
  out << "()";
  return out;
}
template <typename... Args, std::enable_if_t<sizeof...(Args) != 0, int> = 0>
std::ostream& operator<<(std::ostream& out, const std::tuple<Args...>& t) {
  out << "(";
  TuplePrinter<decltype(t), sizeof...(Args)>::print(out, t);
  out << ")";
  return out;
}

template <class T1, class T2>
std::ostream& operator<<(std::ostream& out, const std::pair<T1, T2>& v) {
  out << '<';
  out << v.first << ", " << v.second;
  out << ">";
  return out;
}

template <class T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v) {
  out << '[';
  if (!v.empty()) {
    for (const auto& i : v) {
      out << i << ", ";
    }
    out << "\b\b";  // use two ANSI backspace characters '\b' to overwrite final ", "
  }
  out << "]";
  return out;
}
std::ostream& operator<<(std::ostream& out, const TreeNode* v);

}  // namespace leetcode::lib
