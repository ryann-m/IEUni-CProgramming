# src CMakeLists

# How we do certain lines, just an EXP
#   add_library(name_length name_length.c)
#   target_include_directories(name_length PUBLIC ${PROJECT_SOURCE_DIR}/include)
#   add_executable(main main.c)
#   target_link_libraries(main name_length)

# File practice 10.1.2025
# Executables
add_executable(filePracticeMain filePracticeMain.c)
add_library(filePracticeLibrary filePracticeLibrary.c)

# Library
target_link_libraries(filePracticeMain filePracticeLibrary)

# Directory
target_include_directories(filePracticeLibrary PUBLIC ${PROJECT_SOURCE_DIR}/include)