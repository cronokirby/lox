#pragma once
#include <string>
#include <variant>

namespace lexer {
/// Represents the type a given token has.
///
/// This basically distinguishes the syntactic category something is,
/// while not containing any information about the specific contents that
/// might be present in a given token.
enum class TokenType {
  // Single Character Tokens
  LeftParen,
  RightParen,
  LeftBrace,
  RightBrace,
  Comma,
  Dot,
  Minus,
  Plus,
  Semicolon,
  Slash,
  Star,
  // One or two character tokens
  Bang,
  BangEqual,
  Equal,
  EqualEqual,
  Greater,
  GreaterEqual,
  Less,
  LessEqual,
  // Literals
  Identifier,
  String,
  Number,
  // Keywords
  And,
  Class,
  Else,
  False,
  Fun,
  For,
  If,
  Nil,
  Or,
  Print,
  Return,
  Super,
  This,
  True,
  Var,
  While,
  // EOF
  EndOfFile
};

/// Represents a kind of token emitted by our lexer.
///
/// The Token has information about what syntactic class it belongs to,
/// the string information that produced it, which line it was on,
/// and it might contain data if it's a kind of token that's supposed
/// to hold extra information, like a number or a string token
struct Token {
  const TokenType type;
  const std::string lexeme;
  const int line;
  std::variant<std::string, double> token_data;

  Token(TokenType type, std::string lexeme, int line) noexcept;
  Token(TokenType type, std::string lexeme, int line,
        double double_data) noexcept;
  Token(TokenType type, std::string lexeme, int line,
        std::string string_data) noexcept;
};

} // namespace lexer