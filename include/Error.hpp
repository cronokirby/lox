#pragma once
#include <string>

/// An abstract class for errors that can occurr in when interpreting a program.
///
/// The message for this error isn't known here in the parent, it's up to
/// children to supply the message that they want to show. On the other hand,
/// the metadata about location can be handled here in the parent.
class Error {
public:
  /// The line associated with this error
  const int line;

  /// The file assocaited with this error
  const char *file;

  /// Create a new error occurring at a given line
  ///
  /// @param line the line where an error occurred
  Error(int line);

  /// Create a new error at a given line in a given file
  ///
  /// @param line the line where an error occurred
  /// @param file the name of the file where an error occurred
  Error(int line, const char *file);

  /// Get the message returned by this string
  virtual std::string messsage() const noexcept;
};
