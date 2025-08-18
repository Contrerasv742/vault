cmake_minimum_required(VERSION 4.0.0)
project(vault VERSION 1.0 LANGUAGES CXX)

# Basic configuration
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find Qt packages
find_package(Qt6 REQUIRED COMPONENTS Widgets Gui)

# Fetch JSON parser library
include(FetchContent)
FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
    DOWNLOAD_EXTRACT_TIMESTAMP true
)
FetchContent_MakeAvailable(json)

# Include Source and Header Files
set(SOURCES
    src/app/main.cpp
    src/parser/passwordManager.cpp
    src/crypto/cipher.cpp
    src/crypto/rsa.cpp
    src/crypto/random.cpp
    src/ui/app.cpp
    src/ui/mainpage.cpp
    src/ui/loginScreen.cpp
    src/ui/encryptpage.cpp

    tests/rsa.cpp
)

set(HEADERS
    src/app/main.h
    src/parser/passwordManager.h
    src/crypto/cipher.h
    src/crypto/random.h
    src/crypto/rsa.h
    src/ui/encryptpage.h
    src/ui/app.h
    src/ui/mainpage.h
    src/ui/loginScreen.h

    tests/rsa.h
)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE src)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE 
    Qt6::Widgets
    Qt6::Gui
    nlohmann_json::nlohmann_json
)

# Add debug symbols
# target_compile_options(${PROJECT_NAME} PRIVATE -g)

# Installation rules
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

# Platform-specific deployment
if(WIN32)
    # Windows deployment
    include(InstallRequiredSystemLibraries)
    get_target_property(_qmake_executable Qt6::qmake IMPORTED_LOCATION)
    get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
    find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_qt_bin_dir}")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND "${WINDEPLOYQT_EXECUTABLE}"
            --verbose 0
            --no-compiler-runtime
            --no-angle
            --no-opengl-sw
            \"$<TARGET_FILE:${PROJECT_NAME}>\"
    )
elseif(APPLE)
    # macOS deployment
    get_target_property(_qmake_executable Qt6::qmake IMPORTED_LOCATION)
    get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
    find_program(MACDEPLOYQT_EXECUTABLE macdeployqt HINTS "${_qt_bin_dir}")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND "${MACDEPLOYQT_EXECUTABLE}"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/../.."
            -always-overwrite
    )
else()
    # Linux deployment
    get_target_property(_qmake_executable Qt6::qmake IMPORTED_LOCATION)
    get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
    find_program(LINUXDEPLOYQT_EXECUTABLE linuxdeployqt HINTS "${_qt_bin_dir}")
    if(LINUXDEPLOYQT_EXECUTABLE)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND "${LINUXDEPLOYQT_EXECUTABLE}"
                "$<TARGET_FILE:${PROJECT_NAME}>"
                -always-overwrite
                -unsupported-allow-new-glibc
        )
    endif()
endif()
