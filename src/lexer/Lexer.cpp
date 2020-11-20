#include "Lexer.hpp"
#include "UnexpectedCharacter.hpp"
#include "UnterminatedStringError.hpp"

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

char Lexer::peek() noexcept {
  if (isAtEnd()) {
    return '\0';
  }
  return source[current];
}

bool Lexer::match(char expected) noexcept {
  if (isAtEnd()) {
    return false;
  }
  if (source[current] != expected) {
    return false;
  }
  ++current;
  return true;
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

void Lexer::string() noexcept {
  while (peek() != '"' && !isAtEnd()) {
    if (peek() == '\n') {
      ++line;
    }
    advance();
  }

  if (isAtEnd()) {
    UnterminatedStringError error;
    error.setLine(line);
    reporter.report(error);
    return;
  }

  advance();

  // We make sure to exclude the string delimiters
  const auto text = source.substr(start + 1, current - start - 1);
  addToken(TokenType::String, text);
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
  case '!': {
    addToken(match('=') ? TokenType::BangEqual : TokenType::Bang);
    break;
  }
  case '=': {
    addToken(match('=') ? TokenType::EqualEqual : TokenType::Equal);
    break;
  }
  case '<': {
    addToken(match('=') ? TokenType::LessEqual : TokenType::Less);
    break;
  }
  case '>': {
    addToken(match('=') ? TokenType::GreaterEqual : TokenType::Greater);
    break;
  }
  case '/': {
    if (match('/')) {
      // We need to handle a comment
      while (peek() != '\n' && !isAtEnd()) {
        advance();
      }
    } else {
      addToken(TokenType::Slash);
    }
    break;
  }
  // Ignore whitespace
  case ' ':
  case '\r':
  case '\t':
    break;
  case '\n': {
    ++line;
    break;
  }
  case '"': {
    string();
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