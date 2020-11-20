#pragma once
#include "../ErrorReporter.hpp"
#include "Token.hpp"
#include <string>
#include <vector>

/// Represents a Lexer, which produces tokens by looking over a given string
class Lexer {
  std::string source;
  std::vector<Token> tokens;
  const ErrorReporter &reporter;

  size_t start{0};
  size_t current{0};
  int line{1};

  bool isAtEnd() const noexcept;

  char advance() noexcept;

  void addToken(TokenType) noexcept;
  void addToken(TokenType, double) noexcept;
  void addToken(TokenType, std::string) noexcept;

  void scanToken() noexcept;

public:
  Lexer(std::string source, const ErrorReporter &reporter) noexcept;

  std::vector<Token> scanTokens() noexcept;
};
