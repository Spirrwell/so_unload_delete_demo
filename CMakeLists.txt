cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

project(so_unload)

set(CMAKE_BUILD_RPATH "$ORIGIN")

# See comment in src/exe/main.cpp regarding the usage of this
add_compile_options( "-fno-gnu-unique" )

add_executable(exe src/exe/main.cpp)
target_link_libraries(exe PRIVATE ${CMAKE_DL_LIBS}) #-ldl
target_include_directories(exe PRIVATE include/)

add_library(so MODULE src/so/so.cpp)
target_include_directories(so PRIVATE include/)