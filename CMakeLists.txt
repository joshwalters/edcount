cmake_minimum_required(VERSION 3.7)

# Require c11 standard
set(C_STANDARD 11)
set(C_STANDARD_REQUIRED ON)

project(edcount)
set(BIN_DIR ${edcount}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
file(GLOB SOURCE_FILES src/*.c)
add_executable(edcount ${SOURCE_FILES})
