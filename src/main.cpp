#include "ErrorReporter.hpp"
#include "SimpleError.h"
#include <fstream>
#include <iostream>
#include <string>

/// Read the contents of a file into a string.
///
/// @param file the file to read
std::string readFile(const char *file) {
  using namespace std::string_literals;

  std::ifstream in{file, std::ios::in};
  if (!in) {
    throw std::runtime_error("Failed to read file: "s + file);
  }
  std::string contents;
  in.seekg(0, std::ios::end);
  contents.resize(in.tellg());
  in.seekg(0, std::ios::beg);
  in.read(&contents[0], contents.size());
  return contents;
}

void run(const std::string &source, ErrorReporter &reporter) {
  reporter.report(SimpleError{"Not Implemented Yet!"});
  std::cout << source << '\n';
}

void runFile(const char *file, ErrorReporter &reporter) {
  const auto contents = readFile(file);
  run(contents, reporter);
}

void runPrompt(ErrorReporter &reporter) {
  std::string line;
  for (;;) {
    std::cout << "> ";
    if (!std::getline(std::cin, line)) {
      std::cout << std::endl;
      break;
    }
    run(line, reporter);
  }
}

int main(const int argc, const char **argv) {
  if (argc > 2) {
    std::cout << "Usage: lox <script>\n";
    return 64;
  }
  ErrorReporter reporter;
  if (argc == 2) {
    runFile(argv[1], reporter);
    if (reporter.hadError()) {
      return 65;
    }
  } else {
    runPrompt(reporter);
  }
  return 0;
}
