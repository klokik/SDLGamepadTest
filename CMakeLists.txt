cmake_minimum_required(VERSION 2.8)

project(gamepad_test)

cmake_policy(SET CMP0037 NEW)

set(CMAKE_CXX_FLAGS "-std=c++11 -g")

add_executable(gamepad Gamepad.cpp)
target_link_libraries(gamepad SDL2)