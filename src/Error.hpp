#pragma once
#include <string>

/// An abstract class for errors that can occur in when interpreting a program.
///
/// The message for this error isn't known here in the parent, it's up to
/// children to supply the message that they want to show. On the other hand,
/// the metadata about location can be handled here in the parent.
class Error {
  int _line{0};
  std::string _file;

public:
  /// Get the message returned by this string
  virtual std::string message() const noexcept = 0;

  int getLine() const noexcept;
  void setLine(int line) noexcept;

  const std::string &getFile() const;
  void setFile(const char *file);
};
