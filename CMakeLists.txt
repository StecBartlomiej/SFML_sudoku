cmake_minimum_required(VERSION 3.20)
project(SFML_sudoku)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-Wall -Wextra -pedantic -Werror -O2 )

include_directories(include)

file(GLOB SOURCES
        source/*.cpp
        )

include_directories(source)

# Build SFML
set(BUILD_SHARED_LIBS FALSE)
add_subdirectory(lib/sfml)

add_executable(${PROJECT_NAME} main.cpp ${SOURCES})

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)
