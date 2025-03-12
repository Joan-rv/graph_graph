cmake_minimum_required(VERSION 3.28)
project(graph_graph LANGUAGES C)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "5.5"
    GIT_PROGRESS TRUE
    FIND_PACKAGE_ARGS 5
)
FetchContent_MakeAvailable(raylib)

add_executable(graph_graph src/main.c)
target_link_libraries(graph_graph PRIVATE raylib)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(graph_graph PRIVATE -Wall -Wpedantic -Wextra)
elseif ( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
    target_compile_options(graph_graph PRIVATE /W4)
endif()
