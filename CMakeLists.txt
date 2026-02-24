cmake_minimum_required(VERSION 3.20)
project(vault VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Fetch JSON
include(FetchContent)
FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
    DOWNLOAD_EXTRACT_TIMESTAMP true
)
FetchContent_MakeAvailable(json)

# Build crypto as a shared library
add_library(crypto SHARED
    src/crypto/cipher.cpp
    src/crypto/rsa.cpp
    src/crypto/random.cpp
    src/passwordManager.cpp
)

target_include_directories(crypto PUBLIC src)
target_link_libraries(crypto PRIVATE nlohmann_json::nlohmann_json)

# After building the shared lib, compile the Go TUI
add_custom_target(tui ALL
    COMMAND go build -o ${CMAKE_BINARY_DIR}/vault .
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/src/tui
    DEPENDS crypto
    COMMENT "Building Go TUI..."
)
