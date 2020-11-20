#include "SimpleError.h"

#include <utility>

SimpleError::SimpleError(std::string description)
    : _description(std::move(description)) {
}

void SimpleError::description(std::ostream &out) const noexcept {
  out << _description;
}
