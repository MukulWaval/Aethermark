cmake_minimum_required(VERSION 3.14)
project(aethermark VERSION 1.0.0)

# Ensure C++17 compatibility
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Read version from the VERSION file
file(READ "${CMAKE_SOURCE_DIR}/VERSION" VERSION_INFO)
string(STRIP "${VERSION_INFO}" VERSION_INFO)  # Remove extra spaces/newlines

# Add pybind11
include(FetchContent)
FetchContent_Declare(
    pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11.git
    GIT_TAG v2.9.2
)
FetchContent_MakeAvailable(pybind11)

# Add the aethermark module
add_subdirectory(pybind11)
pybind11_add_module(aethermark src/main.cpp)

# Define VERSION_INFO using the version from the file
target_compile_definitions(aethermark PRIVATE VERSION_INFO="${VERSION_INFO}")

# Set include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Installation rules (optional)
install(TARGETS aethermark LIBRARY DESTINATION lib)
install(FILES ${CMAKE_SOURCE_DIR}/VERSION DESTINATION share/aethermark)
