# CMakeLists.txt

# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(terra LANGUAGES CXX)

# Set the C++ standard (optional but recommended)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# Add the executable by specifying the source file

add_compile_options(
  -g
  -Og
  -Wall
  -Wextra
  -pedantic-errors
  -Wconversion
  -Wsign-conversion
  -Wdouble-promotion
  -Wcast-align
  -Wformat=2
  -Wuninitialized
  -Wnull-dereference
  -Wnon-virtual-dtor
  -Woverloaded-virtual
  -Wdeprecated-copy-dtor
  -Wold-style-cast
  -Wzero-as-null-pointer-constant
  -Wsuggest-override
  -fstack-protector-strong
)

set(TERRA_SOURCES
	src/main.cpp
	src/ant.cpp
	src/renderer.cpp
	src/food.cpp
	src/colony.cpp
	src/qtree.cpp
)

set(BENCHMARK_SOURCES
	src/ant.cpp
	src/renderer.cpp
	src/food.cpp
	src/colony.cpp
	src/qtree.cpp
)

add_executable(terra ${TERRA_SOURCES})
target_link_libraries(terra PRIVATE sfml-graphics sfml-window sfml-system)

add_executable(benchmark_simulation ${BENCHMARK_SOURCES} src/benchmark.cpp)
target_link_libraries(benchmark_simulation PRIVATE benchmark sfml-graphics sfml-window sfml-system)
