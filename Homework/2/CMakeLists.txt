cmake_minimum_required(VERSION 3.22)

project(WaddoupsHomework2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG        e69e5f977d458f2650bb346dadf2ad30c5320281) # 10.2.1
FetchContent_MakeAvailable(fmt)

include(CompilerWarnings.cmake)
waddoups_set_project_warnings()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(main main.cpp)
target_link_libraries(main fmt::fmt)
