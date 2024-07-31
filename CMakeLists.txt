cmake_minimum_required(VERSION 3.10)

# Set the project name
project(CipherProject)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add compiler warnings
if(MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra)
endif()

# Find all .cpp files in the current directory
file(GLOB SOURCES "*.cpp")

# Find all .h files in the current directory
file(GLOB HEADERS "*.h")

# Add an executable target
add_executable(main ${SOURCES} ${HEADERS})

# If you have any libraries to link against, you can use:
# target_link_libraries(main PRIVATE your_library)

# If you need to include directories:
# target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
