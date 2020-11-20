#include "ErrorReporter.hpp"
#include <iostream>

void ErrorReporter::report(const Error &error) {
  _hadError = true;

  std::cerr << "\e[1;31mERROR\e0m [" << error.file << " line " << error.line
            << "]: " << error.messsage();
}

bool ErrorReporter::hadError() const noexcept {
  return _hadError;
}

void ErrorReporter::reset() noexcept {
  _hadError = false;
}