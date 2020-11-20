# We need version 3.12 to not have to rerun cmake when our glob changes
cmake_minimum_required(VERSION 3.12)

project(lox)

include_directories(include)

# Using C++ 17 as our standard, and requiring that standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Create a lox executable from the sources we've gathered
add_executable(lox src/main.cpp src/Error.cpp src/ErrorReporter.cpp src/SimpleError.cpp)
# Standard, but strict compiler options
target_compile_options(lox PRIVATE -Werror -Wall -Wextra)
