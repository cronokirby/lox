#include "Error.hpp"
#include "string"

/// Represents a Simple class of errors with just a string to display
class SimpleError : public Error {
  std::string _description;
public:
  /// Constructor a new SimpleError given a message.
  ///
  /// @param message the message to display to the user
  explicit SimpleError(std::string description);

  void description(std::ostream &out) const noexcept override;
};
