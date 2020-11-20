#include "Error.hpp"

int Error::getLine() const noexcept {
  return _line;
}

void Error::setLine(int line) noexcept {
  _line = line;
}
