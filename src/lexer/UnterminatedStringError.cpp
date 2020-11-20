#include "UnterminatedStringError.hpp"
#include <iostream>

namespace lexer {

void lexer::UnterminatedStringError::description(
    std::ostream &out) const noexcept {
  out << "Unterminated String";
}

} // namespace lexer
