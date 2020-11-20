#include "ErrorReporter.hpp"
#include <iostream>

void ErrorReporter::report(const Error &error) noexcept {
  _hadError = true;

  std::cerr << "\033[1;31mERROR\033[0m [";
  if (!file.empty()) {
    std::cerr << file << " ";
  }
  std::cerr << error.getLine() << "]: ";
  error.description(std::cerr);
  std::cerr << std::endl;
}

bool ErrorReporter::hadError() const noexcept {
  return _hadError;
}

void ErrorReporter::reset() noexcept {
  _hadError = false;
}

ErrorReporter::ErrorReporter(std::string file)
    : file(std::move(file)) {
}
