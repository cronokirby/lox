#pragma once
#include "../ErrorReporter.hpp"
#include "Token.hpp"
#include <string>
#include <vector>

namespace lexer {

/// Represents a Lexer, which produces tokens by looking over a given string
class Lexer {
  std::string source;
  std::vector<Token> tokens;
  ErrorReporter &reporter;

  size_t start{0};
  size_t current{0};
  int line{1};

  bool isAtEnd() const noexcept;

  char advance() noexcept;

  char peek() noexcept;

  char peekNext() noexcept;

  bool match(char) noexcept;

  void addToken(TokenType) noexcept;
  void addToken(TokenType, double) noexcept;
  void addToken(TokenType, std::string) noexcept;

  void string() noexcept;

  void number() noexcept;

  void identifier() noexcept;

  void scanToken() noexcept;

public:
  Lexer(std::string source, ErrorReporter &reporter) noexcept;

  std::vector<Token> scanTokens() noexcept;
};

} // namespace lexer
