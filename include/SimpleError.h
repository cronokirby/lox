#include "Error.hpp"
#include "string"

/// Represents a Simple class of errors with just a string to display
class SimpleError : public Error {
  std::string _message;
public:
  /// Constructor a new SimpleError given a message.
  ///
  /// @param message the message to display to the user
  explicit SimpleError(std::string message);

  std::string message() const noexcept override;
};
