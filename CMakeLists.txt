#cmake_minimum_required(VERSION 3.3)
project(cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -fpermissive")

set(SOURCE_FILES c++11/atom.cpp boost/bind/TestBind.cpp)

add_executable(atom ${SOURCE_FILES})
target_link_libraries(atom pthread)


add_executable(auto_ptr c++11/auto_ptr.cpp)

add_executable(stl_interview stl/stl_interview.cpp)

add_executable(reconnect network/reconnect.cpp)
target_link_libraries(reconnect pthread)

add_executable(server network/server.cpp)
target_link_libraries(server pthread)


add_executable(epoll_ctl_test network/EpollCtl.cpp network/EpollCtlTest.cpp)
target_link_libraries(epoll_ctl_test pthread)


add_executable(TestBind boost/bind/TestBind.cpp)

add_executable(TestThread boost/thread/TestThread.cpp)
target_link_libraries(TestThread pthread)