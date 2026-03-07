cmake_minimum_required(VERSION 3.20)
project(vault VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add cmake module path and include dependencies
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(cmake/Dependencies.cmake)

# Build crypto as a shared library
add_library(crypto SHARED
    src/crypto/cipher.cpp
    src/crypto/encrypt.cpp
    src/crypto/random.cpp
    src/crypto/rsa.cpp
    src/passwordManager.cpp
)

target_include_directories(crypto PUBLIC src)
target_link_libraries(crypto PUBLIC nlohmann_json::nlohmann_json)
target_link_libraries(crypto PUBLIC sodium)

# Main Executable
add_executable(test src/main.cpp)
target_link_libraries(test PRIVATE crypto)

# Compile the Go TUI
add_custom_target(tui ALL
    COMMAND go build -o ${CMAKE_BINARY_DIR}/vault .
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/src/tui
    DEPENDS crypto
    COMMENT "Building Go TUI..."
)
