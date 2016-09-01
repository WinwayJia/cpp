project(main)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
add_subdirectory(lib)
#include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(include)
set(SRC_LIST src/main.c)
add_executable(main ${SRC_LIST})
target_link_libraries(main hello)

