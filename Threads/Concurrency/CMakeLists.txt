cmake_minimum_required(VERSION 3.28)
project(ConcurrencyProject C)

set(CMAKE_C_STANDARD 23)

# include utest folder
include_directories(${PROJECT_SOURCE_DIR}/third_party)

# Library with concurrency functions
add_library(concurrencyLib concurrencyLib.c)

# Test executable
add_executable(concurrencyTest concurrencyTest.c)
target_link_libraries(concurrencyTest concurrencyLib pthread)

# Optional main (not part of tests)
add_executable(concurrencyMain concurrencyMain.c)
target_link_libraries(concurrencyMain concurrencyLib pthread)

enable_testing()
add_test(NAME concurrencyTest COMMAND concurrencyTest)
