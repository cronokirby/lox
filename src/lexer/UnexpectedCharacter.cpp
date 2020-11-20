#include "UnexpectedCharacter.hpp"
#include <iostream>

namespace lexer {

UnexpectedCharacter::UnexpectedCharacter(char unexpected)
    : unexpected(unexpected) {
}
void UnexpectedCharacter::description(std::ostream &out) const noexcept {
  out << "Unexpected Character: " << unexpected;
}

} // namespace lexer
