#pragma once

#include "../Error.hpp"

namespace lexer {

/// Represents an error that occurred because a string wasn't terminated.
///
/// This will happen if we see an opening `"`, but then no closing `"`
/// until the end of the file.
struct UnterminatedStringError : public Error {
  void description(std::ostream &out) const noexcept override;
};

} // namespace lexer
