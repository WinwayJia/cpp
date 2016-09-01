project(HELLO)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
#include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(include)
set(SRC_LIST src/main.c src/hello.c)
add_executable(hello ${SRC_LIST})

