#include "Error.hpp"

int Error::getLine() const noexcept {
  return _line;
}

void Error::setLine(int line) noexcept {
  _line = line;
}

const std::string& Error::getFile() const {
  return _file;
}

void Error::setFile(const char *file) {
  _file = file;
}
