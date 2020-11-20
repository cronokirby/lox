#include "Token.h"

#include <utility>

Token::Token(TokenType type, std::string lexeme, int line)
    : type{type}
    , lexeme{std::move(lexeme)}
    , line{line} {
}
Token::Token(TokenType type, std::string lexeme, int line, double double_data)
    : type{type}
    , lexeme{std::move(lexeme)}
    , line{line}
    , token_data{double_data} {
}
Token::Token(TokenType type, std::string lexeme, int line,
             std::string string_data)
    : type{type}
    , lexeme{std::move(lexeme)}
    , line{line}
    , token_data{std::move(string_data)} {
}
