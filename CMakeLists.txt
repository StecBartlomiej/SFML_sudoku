cmake_minimum_required(VERSION 3.20)
project(SFML_sudoku)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-Wall -Wextra -pedantic -Werror -O2 )

file(GLOB SOURCES
        source/*.cpp
        source/*.hpp
        source/*.h
        )

include_directories(source)

## If you want to link SFML statically
#set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
## Path to builded SFML directory
set(SFML_DIR "C:/Users/barte/Documents/C++/Libs/SFML/build")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

IF (WIN32)
    ## WIN32 - for hiding a console window
    add_executable(${PROJECT_NAME} WIN32 main.cpp ${SOURCES} )
ELSE()
    add_executable(${PROJECT_NAME} main.cpp ${SOURCES} )
ENDIF()

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)

## Copy a .dll files
if(WIN32)
    file(GLOB BINARY_SFML_DLLS "${SFML_DIR}/lib/*.dll")
    file(COPY ${BINARY_SFML_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()
