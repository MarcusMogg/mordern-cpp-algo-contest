#include "token.h"

#include <cctype>
#include <format>
#include <iostream>

namespace leetcode::lib {
SimpleGenerator<Token> NextToken(std::string_view data) {
  Token t{.type = Token::TokenType::kNone};
  for (int i = 0; i < data.size(); ++i) {
    switch (t.type) {
      case Token::TokenType::kNone:
        if (std::isspace(data[i]) != 0) {
          break;
        }
        if (std::isdigit(data[i]) != 0 || data[i] == '-') {
          t.type = Token::TokenType::kInteger;
          t.raw_data = std::string_view(data.data() + i, 1);
          break;
        }
        switch (data[i]) {
          case '[':
            co_yield {Token::TokenType::kSquareBracketsLeft, "["};
            break;
          case ']':
            co_yield {Token::TokenType::kSquareBracketsRight, "]"};
            break;
          case ',':
            co_yield {Token::TokenType::kComma, ","};
            break;
          case '\"':
            t.type = Token::TokenType::kString;
            t.raw_data = std::string_view(data.data() + i, 1);
            break;
          case 'n':
            t.type = Token::TokenType::kNull;
            t.raw_data = std::string_view(data.data() + i, 1);
            break;
          default:
            throw ParseError(std::format("inlegal char {} in kNone", data[i]));
        }
        break;
      case Token::TokenType::kNull:
        if (std::islower(data[i]) != 0) {
          t.raw_data = std::string_view(t.raw_data.data(), t.raw_data.size() + 1);
          break;
        }
        if (std::isspace(data[i]) != 0 || Among(data[i], ']', ',')) {
          if (t.raw_data != "null") {
            throw ParseError(std::format("know token {} in kNull", t.raw_data));
          }
          co_yield t;
          t.type = Token::TokenType::kNone;
          i--;
          break;
        }
        throw ParseError(std::format("inlegal char {} in kNull", data[i]));
      case Token::TokenType::kInteger:
        if (std::isdigit(data[i]) != 0) {
          t.raw_data = std::string_view(t.raw_data.data(), t.raw_data.size() + 1);
          break;
        }
        if (std::isspace(data[i]) != 0 || Among(data[i], ']', ',')) {
          co_yield t;
          t.type = Token::TokenType::kNone;
          i--;
          break;
        }
        throw ParseError(std::format("inlegal char {} in kInteger", data[i]));
      case Token::TokenType::kString:
        if (data[i] == '\\') {
          if (i + 1 == data.size()) {
            throw ParseError("input not a string");
          }
          i++;
          t.raw_data = std::string_view(t.raw_data.data(), t.raw_data.size() + 2);
        } else if (data[i] == '\"') {
          t.raw_data = t.raw_data.substr(1);  // skip first "
        } else {
          t.raw_data = std::string_view(t.raw_data.data(), t.raw_data.size() + 1);
        }
      case Token::TokenType::kSquareBracketsLeft:
      case Token::TokenType::kSquareBracketsRight:
      case Token::TokenType::kComma:
      case Token::TokenType::kEof:
        throw ParseError(std::format("unexcepted status {} ", static_cast<int>(t.type)));
    }
  }
  if (t.type != Token::TokenType::kNone) {
    co_yield t;
  }
}
}  // namespace leetcode::lib