#pragma once

// for clangd
// #define __cpp_consteval 202211L

#include <format>
#include <source_location>
#include <stdexcept>

namespace leetcode::lib {

struct ParseError : std::runtime_error {
  std::source_location loc;

  explicit ParseError(
      std::string_view str, const std::source_location& loc = std::source_location::current())
      : std::runtime_error(std::format("Throw at {}:{} | {}", loc.file_name(), loc.line(), str)) {}
};
}  // namespace leetcode::lib