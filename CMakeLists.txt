cmake_minimum_required(VERSION 3.10)
project(ChessMatch)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set source directory
set(SRC_DIR src)

# Set build directory
set(BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR}/build)

# Ensure the build directory exists
file(MAKE_DIRECTORY ${BUILD_DIR})

# Find all source files in src directory and its subfolders
file(GLOB_RECURSE SRCS "${SRC_DIR}/*.cpp")

# Set executable target
add_executable(ChessMatch ${SRCS})

# Include directories for target
target_include_directories(ChessMatch PRIVATE ${SRC_DIR})

# Set output directory
set_target_properties(ChessMatch PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR}
)
