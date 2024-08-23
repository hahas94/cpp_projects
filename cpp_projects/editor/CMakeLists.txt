# Minimum CMake version required
cmake_minimum_required(VERSION 3.25)

# Project name and version
project(EditorProgram VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add global compile options for all targets
add_compile_options(-Wall -Wextra -Werror -Wfatal-errors -Wpedantic -Weffc++ -Wold-style-cast
                    -D_GLIBCXX_DEBUG -fmax-errors=1 -fsanitize=undefined -fsanitize=address
)

# Add source files
set(SOURCES
        editor.cpp
        editor.hpp
)

# Add the main executable
add_executable(EditorApp edit.cpp editor.cpp editor.hpp)

# Add the test executable
add_executable(EditorTest editor_test.cpp ${SOURCES})

# Optionally link libraries if needed (e.g., for testing)
target_link_libraries(EditorTest PRIVATE ${CMAKE_SOURCE_DIR}/../../test/test_main.o)
target_link_libraries(EditorTest PRIVATE -fsanitize=undefined -fsanitize=address)
target_link_libraries(EditorApp PRIVATE -fsanitize=undefined -fsanitize=address)

# Enable testing (optional if you want to use CTest)
enable_testing()

# Add test cases (optional)
add_test(NAME RunEditorTests COMMAND EditorTest)