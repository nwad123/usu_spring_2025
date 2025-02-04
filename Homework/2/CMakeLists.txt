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

set(SOLVERS solvers/serial.cpp solvers/parallel.cpp solvers/tree.cpp)
set(ARG_PARSER src/parse_args.cpp)

set(OPTS -DNDEBUG -O3 -flto -mtune=native -march=native)
# set(OPTS -DDEBUG -O0 -g3) # uncomment for debug

# Command line interface application
add_executable(cli cli.cpp ${ARG_PARSER} ${SOLVERS})
target_link_libraries(cli fmt::fmt)
target_compile_options(cli PRIVATE ${OPTS})

# Auto tester for simple params 
add_executable(test test.cpp ${SOLVERS})
target_link_libraries(test fmt::fmt)
target_compile_options(test PRIVATE ${OPTS})

# Auto program for generating output with different parameters
add_executable(auto auto.cpp ${SOLVERS})
target_link_libraries(auto fmt::fmt)
target_compile_options(auto PRIVATE ${OPTS})
