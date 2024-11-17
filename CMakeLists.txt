cmake_minimum_required(VERSION 3.5)
project(cs106l)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_FILES cs106l-assignments/assign1/main.cpp cs106l-assignments/assign1/utils.cpp)

add_executable(cs106l ${SOURCE_FILES})

# Set the C++ Standard
set(CMAKE_CXX_STANDARD 17)

# Set the compiling flags
set(CMAKE_CXX_FLAGS "-Werror -Wpedantic -Wall -Wextra -Wvla -Wno-unused-result -Wconversion")