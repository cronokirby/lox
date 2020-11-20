#include "ErrorReporter.hpp"
#include <iostream>

void ErrorReporter::report(const Error &error) noexcept {
  _hadError = true;

  std::cerr << "\033[1;31mERROR\033[0m [" << error.getFile() << " line " << error.getLine()
            << "]: " << error.message() << std::endl;
}

bool ErrorReporter::hadError() const noexcept {
  return _hadError;
}

void ErrorReporter::reset() noexcept {
  _hadError = false;
}
