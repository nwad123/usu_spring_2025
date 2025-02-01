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

set(SOLVERS solvers/serial.cpp solvers/parallel.cpp)

add_executable(cli cli.cpp ${SOLVERS})
target_link_libraries(main fmt::fmt)
