#include "UnexpectedCharacter.hpp"

namespace lexer {

UnexpectedCharacter::UnexpectedCharacter(char unexpected)
    : unexpected(unexpected) {
}

std::string UnexpectedCharacter::message() const noexcept {
  return std::string{"Unexpected Character: "} + unexpected;
}

} // namespace lexer
