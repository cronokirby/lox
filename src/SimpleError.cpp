#include "SimpleError.h"

#include <utility>

std::string SimpleError::message() const noexcept {
  return _message;
}

SimpleError::SimpleError(std::string message)
    : _message(std::move(message)) {
}
