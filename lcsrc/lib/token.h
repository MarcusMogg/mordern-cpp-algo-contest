#pragma once

#include <coroutine>
#include <format>
#include <iterator>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string_view>
#include <utility>

#include "parser_error.h"

namespace leetcode::lib {
struct GeneratorEnd {};

template <typename HandleType, typename ValueType>
struct GeneratorIter {
  using iterator_category = std::input_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using value_type = std::remove_reference_t<ValueType>;
  using reference = std::conditional_t<std::is_reference_v<ValueType>, ValueType, ValueType&>;
  using pointer = std::add_pointer_t<ValueType>;

  bool operator!=(const GeneratorEnd& /*unused*/) { return !h.done(); }
  GeneratorIter& operator++() {
    h();
    return *this;
  }
  void operator++(int) { (void)operator++(); }
  value_type& operator*() const noexcept { return h.promise().value(); }

  HandleType h;
};

template <typename T>
class SimpleGenerator {
 public:
  struct promise_type;
  using handle_type = std::coroutine_handle<promise_type>;
  struct promise_type {
    using pointer = std::add_pointer_t<T>;
    pointer value_;

    auto co() { return handle_type::from_promise(*this); }
    auto get_return_object() { return SimpleGenerator(co()); }
    std::suspend_always initial_suspend() { return {}; }
    std::suspend_always final_suspend() noexcept { return {}; }
    void unhandled_exception() { throw; }

    std::suspend_always yield_value(T& value) {
      value_ = std::addressof(value);
      return {};
    }
    std::suspend_always yield_value(T&& value) {
      value_ = std::addressof(value);
      return {};
    }
    void return_void() {}

    T& value() { return *value_; }
  };

  explicit SimpleGenerator(handle_type h) : h_(h) {}
  ~SimpleGenerator() {
    if (h_) {
      h_.destroy();
    }
  }

  using iterator = GeneratorIter<handle_type, T>;

  auto end() const { return GeneratorEnd{}; }
  auto begin() {
    auto it = GeneratorIter<handle_type, T>{h_};
    if (!begin_) {
      ++it;
      begin_ = true;
    }
    return it;
  }

 private:
  handle_type h_;
  bool begin_ = false;
};

struct Token {
  enum class TokenType {
    kNone = 0,
    kNull = 1,
    kInteger = 2,
    kString = 3,
    kSquareBracketsLeft = 4,
    kSquareBracketsRight = 5,
    kComma = 6,
    kEof = 7,
    kBool = 8,
  };

  TokenType type;
  std::string_view raw_data;
};

template <class T, class... Args>
bool Among(T target, Args... args) {
  return ((target == args) || ...);
}

template <class T, class... Args>
void Excepted(T target, Args... args) {
  if (!Among(target, args...)) {
    throw ParseError(std::format("target {} no in excepted status ", target));
  }
}

SimpleGenerator<Token> NextToken(std::string_view data);
}  // namespace leetcode::lib