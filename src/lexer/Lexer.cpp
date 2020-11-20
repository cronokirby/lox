#include "Lexer.hpp"
#include "UnexpectedCharacter.hpp"

namespace lexer {

Lexer::Lexer(std::string source, ErrorReporter &reporter) noexcept
    : source(std::move(source))
    , reporter(reporter) {
}

bool Lexer::isAtEnd() const noexcept {
  return current >= source.size();
}

char Lexer::advance() noexcept {
  ++current;
  return source[current - 1];
}

void Lexer::addToken(TokenType type) noexcept {
  const auto text = source.substr(start, current - start);
  tokens.emplace_back(Token{type, text, line});
}

void Lexer::addToken(TokenType type, double double_data) noexcept {
  const auto text = source.substr(start, current - start);
  tokens.emplace_back(Token{type, text, line, double_data});
}

void Lexer::addToken(TokenType type, std::string string_data) noexcept {
  const auto text = source.substr(start, current - start);
  tokens.emplace_back(Token{type, text, line, std::move(string_data)});
}

void Lexer::scanToken() noexcept {
  const auto c = advance();
  switch (c) {
  case '(': {
    addToken(TokenType::LeftParen);
    break;
  }
  case ')': {
    addToken(TokenType::RightParen);
    break;
  }
  case '{': {
    addToken(TokenType::LeftBrace);
    break;
  }
  case ',': {
    addToken(TokenType::Comma);
    break;
  }
  case '.': {
    addToken(TokenType::Dot);
    break;
  }
  case '-': {
    addToken(TokenType::Minus);
    break;
  }
  case '+': {
    addToken(TokenType::Plus);
    break;
  }
  case ';': {
    addToken(TokenType::Semicolon);
    break;
  }
  case '*': {
    addToken(TokenType::Star);
    break;
  }
  default: {
    UnexpectedCharacter error{c};
    error.setLine(line);
    reporter.report(error);
    break;
  }
  }
}

std::vector<Token> Lexer::scanTokens() noexcept {
  while (!isAtEnd()) {
    start = current;
    scanToken();
  }
  tokens.emplace_back(Token{TokenType::EndOfFile, "", line});
  return tokens;
}

} // namespace lexer