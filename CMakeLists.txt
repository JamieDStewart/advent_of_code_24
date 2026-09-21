# Advent of Code 2024
#
# The Visual Studio solution (AoC_2024.sln) remains the day-to-day way to work
# on this. This CMake file exists so the same sources build with gcc/clang on
# CI, and so the parent Advent_of_Code repository can add this year as a
# subdirectory and test every year in one pass.

cmake_minimum_required( VERSION 3.20 )

project( aoc_2024 LANGUAGES CXX )

set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

file( GLOB AOC_2024_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp" )
file( GLOB AOC_2024_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.h" )

add_executable( aoc_2024 ${AOC_2024_SOURCES} ${AOC_2024_HEADERS} )

target_include_directories( aoc_2024 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/source" )

if( MSVC )
	target_compile_options( aoc_2024 PRIVATE /W4 )
else()
	target_compile_options( aoc_2024 PRIVATE -Wall -Wextra -Wno-unused-parameter )
endif()

# Keep the binary somewhere predictable so the cross-year test runner can find
# it without having to know about per-generator layout.
set_target_properties( aoc_2024 PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY             "${CMAKE_BINARY_DIR}/bin"
	RUNTIME_OUTPUT_DIRECTORY_DEBUG       "${CMAKE_BINARY_DIR}/bin"
	RUNTIME_OUTPUT_DIRECTORY_RELEASE     "${CMAKE_BINARY_DIR}/bin"
	RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/bin"
)
