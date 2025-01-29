cmake_minimum_required(VERSION 3.22)

project(WaddoupsHomework2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CompilerWarnings.cmake)
waddoups_set_project_warnings()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(main main.cpp)
