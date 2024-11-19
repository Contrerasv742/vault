cmake_minimum_required(VERSION 3.16)
project(vault VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find Qt packages
find_package(Qt6 REQUIRED COMPONENTS Widgets Gui)

# Add the src directory to the include path
include_directories(${CMAKE_SOURCE_DIR}/src)

# Fetch JSON parser library
include(FetchContent)
FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(json)

# Collect all the source files from the src directory
file(GLOB SOURCES
    "src/*.cpp"
    "src/*.h"
)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE 
    Qt6::Widgets
    Qt6::Gui
    nlohmann_json::nlohmann_json  # Remove 'foo PRIVATE' - this was incorrect
)

# Add debug symbols
target_compile_options(${PROJECT_NAME} PRIVATE -g)
