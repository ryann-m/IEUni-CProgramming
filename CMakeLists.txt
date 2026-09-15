# MAIN CmakeLists.txt in homeWork pt2 (which is the content after the 1st midterm)

# Setup
cmake_minimum_required(VERSION 3.21)
project(homeworkPt2 VERSION 1.0 LANGUAGES C)
set(CMAKE_C_STANDARD 23)

# Directories
include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src)

# Testing
enable_testing()
add_subdirectory(tests)