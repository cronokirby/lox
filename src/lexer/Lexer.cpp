#include "Lexer.hpp"
#include "UnexpectedCharacter.hpp"
#include "UnterminatedStringError.hpp"
#include <unordered_map>

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

char Lexer::peekNext() noexcept {
  if (current + 1 >= source.size()) {
    return '\0';
  }
  return source[current + 1];
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

static constexpr bool isDigit(char c) {
  return c >= '0' && c <= '9';
}

void Lexer::number() noexcept {
  while (isDigit(peek())) {
    advance();
  }
  if (peek() == '.' && isDigit(peekNext())) {
    advance();
    while (isDigit(peek())) {
      advance();
    }
  }
  const auto text = source.substr(start, current - start);
  addToken(TokenType::Number, std::stod(text));
}

// Yeah, this might be a bit ugly, but ultimately I don't think is really
// gonna cause many issues
const static std::unordered_map<std::string, TokenType> keywords{
    {"and", TokenType::And},       {"class", TokenType::Class},
    {"else", TokenType::Else},     {"false", TokenType::False},
    {"for", TokenType::For},       {"fun", TokenType::Fun},
    {"if", TokenType::If},         {"nil", TokenType::Nil},
    {"or", TokenType::Or},         {"print", TokenType::Print},
    {"return", TokenType::Return}, {"super", TokenType::Super},
    {"this", TokenType::This},     {"true", TokenType::True},
    {"var", TokenType::Var},       {"while", TokenType::While}};

void Lexer::identifier() noexcept {
  while (isalnum(peek())) {
    advance();
  }

  const auto text = source.substr(start, current - start);
  const auto it = keywords.find(text);
  if (it != keywords.end()) {
    addToken(it->second);
  } else {
    addToken(TokenType::Identifier, text);
  }
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
    if (isDigit(c)) {
      number();
    } else if (isalpha(c)) {
      identifier();
    } else {
      UnexpectedCharacter error{c};
      error.setLine(line);
      reporter.report(error);
    }

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
