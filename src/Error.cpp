#include "Error.hpp"

Error::Error(int line) : line{line} {
}

Error::Error(int line, const char *file) : line{line}, file{file} {
}
