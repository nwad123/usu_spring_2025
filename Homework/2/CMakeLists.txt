cmake_minimum_required(VERSION 3.22)

project(WaddoupsHomework2)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG        9cf9f38eded63e5e0fb95cd536ba51be601d7fa2)
FetchContent_MakeAvailable(fmt)

include(CompilerWarnings.cmake)
waddoups_set_project_warnings()

include_directories(include)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOLVERS solvers/serial.cpp solvers/parallel.cpp solvers/static_parallel.cpp)
set(SOURCES src/parse_args.cpp)

# Add optimizations (comment out to remove)
set(CMAKE_BUILD_TYPE Release)

# Command line interface application
add_executable(cli cli.cpp ${SOURCES} ${SOLVERS})
target_link_libraries(cli fmt::fmt)
target_compile_options(cli PUBLIC -O3 -flto -mtune=native -march=native)

# Auto tester for different parameters
add_executable(auto auto.cpp ${SOURCES} ${SOLVERS})
target_link_libraries(auto fmt::fmt)
target_compile_options(auto PUBLIC -O3 -flto -mtune=native -march=native)
