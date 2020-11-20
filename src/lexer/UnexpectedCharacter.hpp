//
// Created by lucas on 11/20/20.
//

#pragma once

#include "../Error.hpp"

namespace lexer {

/// Represents an error the lexer can throw if it encounters an unexpected
/// character
class UnexpectedCharacter : public Error {
  const char unexpected;

public:
  /// Create a new error given the character we weren't expecting
  ///
  /// @param unexpected the unexpected character
  explicit UnexpectedCharacter(char unexpected);

  std::string message() const noexcept override;
};

} // namespace lexer
