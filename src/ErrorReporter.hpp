#pragma once

#include "Error.hpp"

/// ErrorReporter allows us to easily report instances of the `Error` class.
///
/// We can report multiple errors, and then check whether or not any errors
/// have occurred, using the `hadError()` method.
class ErrorReporter {
  bool _hadError{false};

  std::string file;

public:
  ErrorReporter() = default;
  explicit ErrorReporter(std::string file);

  /// Report that an error happened
  ///
  /// @param error the error we want to raise
  void report(const Error &error) noexcept;

  /// Check whether or not we experienced an error
  bool hadError() const noexcept;

  /// Reset the state of the error reporter, as if no errors had been reported
  void reset() noexcept;
};
